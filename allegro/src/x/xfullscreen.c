#include "allegro5/internal/aintern_xglx.h"

ALLEGRO_DEBUG_CHANNEL("display")

#ifdef ALLEGRO_XWINDOWS_WITH_XF86VIDMODE

static int check_xf86_vidmode_ext(ALLEGRO_SYSTEM_XGLX *s)
{
   int x, y;

   return XF86VidModeQueryExtension(s->gfxdisplay, &x, &y)
      && XF86VidModeQueryVersion(s->gfxdisplay, &x, &y);
}

static int get_num_display_modes(ALLEGRO_SYSTEM_XGLX *s)
{
   if (!check_xf86_vidmode_ext(s))
      return 0;

   if (!XF86VidModeGetAllModeLines(s->gfxdisplay, 0, &s->modes_count, &s->modes))
      return 0;

   return s->modes_count;
}

int _al_xglx_get_num_display_modes(void)
{
   return get_num_display_modes((void *)al_get_system_driver());
}

static ALLEGRO_DISPLAY_MODE *get_display_mode(ALLEGRO_SYSTEM_XGLX *s,
   int i, ALLEGRO_DISPLAY_MODE *mode)
{
   if (!s->modes)
      return NULL;

   mode->width = s->modes[i]->hdisplay;
   mode->height = s->modes[i]->vdisplay;
   mode->format = 0;
   mode->refresh_rate = 0;

   return mode;
}

ALLEGRO_DISPLAY_MODE *_al_xglx_get_display_mode(
   int i, ALLEGRO_DISPLAY_MODE *mode)
{
   return get_display_mode((void *)al_get_system_driver(), i, mode);
}

bool _al_xglx_fullscreen_set_mode(ALLEGRO_SYSTEM_XGLX *s,
   int w, int h, int format, int refresh_rate)
{
   /* GCC complains about mode being uninitialized without this: */
   ALLEGRO_DISPLAY_MODE mode = mode; 
   ALLEGRO_DISPLAY_MODE mode2;
   int i;
   int n;

   n = get_num_display_modes(s);
   if (!n)
      return false;

   /* Find all modes with correct parameters. */
   int possible_modes[n];
   int possible_count = 0;
   for (i = 0; i < n; i++) {
      if (!get_display_mode(s, i, &mode)) {
         continue;
      }
      if (mode.width == w && mode.height == h &&
         (format == 0 || mode.format == format) &&
         (refresh_rate == 0 || mode.refresh_rate == refresh_rate))
      {
         possible_modes[possible_count++] = i;
      }
   }
   if (!possible_count)
      return false;

   /* Choose mode with highest refresh rate. */
   int best_mode = possible_modes[0];
   get_display_mode(s, best_mode, &mode);
   for (i = 1; i < possible_count; i++) {
      if (!get_display_mode(s, possible_modes[i], &mode2))  {
         continue;
      }
      if (mode2.refresh_rate > mode.refresh_rate) {
         mode = mode2;
         best_mode = possible_modes[i];
      }
   }

   ALLEGRO_INFO("best mode [%d] = (%d, %d)\n", best_mode,
      s->modes[best_mode]->hdisplay, s->modes[best_mode]->vdisplay);

   if (!XF86VidModeSwitchToMode(s->gfxdisplay, 0, s->modes[best_mode])) {
      ALLEGRO_ERROR("xfullscreen: XF86VidModeSwitchToMode failed\n");
      return false;
   }

   return true;
}

void _al_xglx_fullscreen_to_display(ALLEGRO_SYSTEM_XGLX *s,
   ALLEGRO_DISPLAY_XGLX *d)
{
   int x, y;
   Window child;

   /* First, make sure the mouse stays inside the window. */
   XGrabPointer(s->gfxdisplay, d->window, False,
      PointerMotionMask | ButtonPressMask | ButtonReleaseMask,
      GrabModeAsync, GrabModeAsync, d->window, None, CurrentTime);
   //FIXME: handle possible errors here
   s->pointer_grabbed = true;

   XTranslateCoordinates(s->gfxdisplay, d->window,
      RootWindow(s->gfxdisplay, d->xscreen), 0, 0, &x, &y, &child);
   XF86VidModeSetViewPort(s->gfxdisplay, 0, x, y);
}

void _al_xglx_store_video_mode(ALLEGRO_SYSTEM_XGLX *s)
{
   int n;
   int i;

   ALLEGRO_DEBUG("xfullscreen: _al_xglx_store_video_mode\n");

   n = get_num_display_modes(s);
   if (n == 0) {
      /* XXX what to do here? */
      return;
   }

   s->original_mode = s->modes[0];

   for (i = 0; i < n; i++) {
      ALLEGRO_DEBUG("mode[%d] = (%d, %d)\n",
         i, s->modes[i]->hdisplay, s->modes[i]->vdisplay);
   }
   ALLEGRO_INFO("xfullscreen: original mode = (%d, %d)\n",
      s->original_mode->hdisplay, s->original_mode->vdisplay);
}

void _al_xglx_restore_video_mode(ALLEGRO_SYSTEM_XGLX *s)
{
   Bool ok;

   ASSERT(s->original_mode);
   ALLEGRO_DEBUG("xfullscreen: _al_xglx_restore_video_mode (%d, %d)\n",
      s->original_mode->hdisplay, s->original_mode->vdisplay);

   ok = XF86VidModeSwitchToMode(s->gfxdisplay, 0, s->original_mode);
   if (!ok) {
      ALLEGRO_ERROR("xfullscreen: XF86VidModeSwitchToMode failed\n");
   }

   if (s->pointer_grabbed) {
      XUngrabPointer(s->gfxdisplay, CurrentTime);
      s->pointer_grabbed = false;
   }

   /* This is needed, at least on my machine, or the program may terminate
    * before the screen mode is actually reset. --pw
    */
   XFlush(s->gfxdisplay);
}

void _al_xglx_free_mode_infos(ALLEGRO_SYSTEM_XGLX *s)
{
   int i;

   if (s->modes_count > 0) {
      for (i = 0; i < s->modes_count; i++) {
         if (s->modes[i]->privsize > 0) {
            XFree(s->modes[i]->private);
         }
      }
      XFree(s->modes);

      s->modes_count = 0;
      s->modes = NULL;
      s->original_mode = NULL;
   }
}

#else /* !ALLEGRO_XWINDOWS_WITH_XF86VIDMODE */

int _al_xglx_get_num_display_modes(void)
{
   return 0;
}

ALLEGRO_DISPLAY_MODE *_al_xglx_get_display_mode(int index,
   ALLEGRO_DISPLAY_MODE *mode)
{
   (void)index;
   (void)mode;
   return NULL;
}

bool _al_xglx_fullscreen_set_mode(ALLEGRO_SYSTEM_XGLX *s,
   int w, int h, int format, int refresh_rate)
{
   (void)s;
   (void)w;
   (void)h;
   (void)format;
   (void)refresh_rate;
   return false;
}

void _al_xglx_fullscreen_to_display(ALLEGRO_SYSTEM_XGLX *s,
   ALLEGRO_DISPLAY_XGLX *d)
{
   (void)s;
   (void)d;
}

void _al_xglx_store_video_mode(ALLEGRO_SYSTEM_XGLX *s)
{
   (void)s;
}

void _al_xglx_restore_video_mode(ALLEGRO_SYSTEM_XGLX *s)
{
   (void)s;
}

void _al_xglx_free_mode_infos(ALLEGRO_SYSTEM_XGLX *s)
{
   (void)s;
}

#endif /* !ALLEGRO_XWINDOWS_WITH_XF86VIDMODE */

static bool got_atoms;
static Atom _NET_WM_STATE;
static Atom _NET_WM_STATE_FULLSCREEN;
#define X11_ATOM_STRING(x) x = XInternAtom(x11, #x, False);

void _al_xglx_toggle_fullscreen_window(ALLEGRO_DISPLAY *display, bool onoff)
{
   ALLEGRO_SYSTEM_XGLX *system = (void *)al_get_system_driver();
   ALLEGRO_DISPLAY_XGLX *glx = (ALLEGRO_DISPLAY_XGLX *)display;
   Display *x11 = system->x11display;
   
   if (!got_atoms) {
      X11_ATOM_STRING(_NET_WM_STATE)
      X11_ATOM_STRING(_NET_WM_STATE_FULLSCREEN)
      got_atoms = true;
   }

   XEvent xev;
   xev.xclient.type = ClientMessage;
   xev.xclient.serial = 0;
   xev.xclient.send_event = True;
   xev.xclient.message_type = _NET_WM_STATE;
   xev.xclient.window = glx->window;
   xev.xclient.format = 32;
   xev.xclient.data.l[0] = onoff ? 1 : 0; /* 0 = off, 1 = on, 2 = toggle */
   xev.xclient.data.l[1] = _NET_WM_STATE_FULLSCREEN;
   xev.xclient.data.l[2] = 0;
   xev.xclient.data.l[3] = 0;
   xev.xclient.data.l[4] = 0;

   XSendEvent(x11, DefaultRootWindow(x11), False,
      SubstructureRedirectMask | SubstructureNotifyMask, &xev);
}

/* vim: set sts=3 sw=3 et: */