#include <allegro.h>
/* Frame rate demo     */
/* By Pete 2001        */
/* Ex.X 'random access' frames */

int running;
BITMAP* osb;

volatile unsigned int frames, fps;
void second_counter(void)
{
	fps=frames;
	frames=0;
} END_OF_FUNCTION(second_counter);
int timewaster_delay;
extern void do_prog(void);

volatile unsigned int ticks;
void ticker(void)
{
	++ticks;
} END_OF_FUNCTION(ticker);

int main(void)
{
	unsigned int ofr;
	BITMAP* spr;
	allegro_init();
	install_keyboard();
	set_gfx_mode(GFX_AUTODETECT, 320, 200, 0,0);
	osb=create_bitmap(150, 150);

	spr=create_bitmap(50,50);
	/* draw a stupid cross */
	clear(spr);
	rectfill(spr,0,20,50,30,192);
	rectfill(spr,20,0,30,50,64);

	running=1;
	LOCK_FUNCTION(second_counter);
	LOCK_VARIABLE(fps);
	LOCK_VARIABLE(frames);
	LOCK_FUNCTION(ticker);
	LOCK_VARIABLE(ticks);
	frames=timewaster_delay=0;
	ofr=0;
	install_int_ex(second_counter, BPS_TO_TIMER(1));
	install_int_ex(ticker, BPS_TO_TIMER(25));
	while (running && (key[KEY_ESC]==0))
	{
		/* monitor fr */
		textprintf(screen, font, 0, 0, 255, "FPS: %05d Waste: %03dms", fps, timewaster_delay);

		/* do program logic */
		do_prog();

		/* draw graphics */
		clear(osb);
		rotate_sprite(osb, spr, 50, 50, itofix(ticks&0xff));

		/* no time control */           
		++frames;

		blit(osb, screen, 0, 0, (SCREEN_W-osb->w)/2, (SCREEN_H-osb->h)/2, osb->w, osb->h);
	}
	set_gfx_mode(GFX_TEXT, 0,0,0,0);
	return 0;
} END_OF_MAIN();

void do_prog(void)
{
	static int in_k=0;
	/* Waste some time: a real program would be doing useful work here */
	rest(timewaster_delay);
	if (in_k && (key[KEY_PLUS_PAD] || key[KEY_MINUS_PAD]))
		return;
	in_k=0;
	if (key[KEY_PLUS_PAD]) 
	{
		timewaster_delay+=10;
		if (timewaster_delay>200) timewaster_delay=0;
		in_k=1;
	}
	if (key[KEY_MINUS_PAD]) 
	{
		timewaster_delay-=10;
		if (timewaster_delay<0) timewaster_delay=200;
		in_k=1;
	}
}
