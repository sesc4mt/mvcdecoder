#ifndef AINTXGLX_H
#define AINTXGLX_H

ALLEGRO_DISPLAY_INTERFACE *_al_display_xglx_driver(void);
ALLEGRO_SYSTEM_INTERFACE *_al_system_xglx_driver(void);
ALLEGRO_BITMAP_INTERFACE *_al_bitmap_xglx_driver(void);
ALLEGRO_KEYBOARD_DRIVER *_al_xwin_keyboard_driver(void);
ALLEGRO_MOUSE_DRIVER *_al_xwin_mouse_driver(void);

#endif
