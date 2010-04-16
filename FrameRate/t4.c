#include <allegro.h>
/* Frame rate demo     */
/* By Pete 2001        */
/* Ex.4 ticker control */
/* with skipping       */

#define G_DELAY 25

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
        int x, y, dx, dy;
        unsigned int ofr;
        allegro_init();
        install_keyboard();
        set_gfx_mode(GFX_AUTODETECT, 320, 200, 0,0);
        osb=create_bitmap(150, 150);
        running=1;
        x=49; y=37;
        dx=1; dy=1;
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
                textprintf(screen, font, 0, 0, 255, "FPS: %05d Waste: %dms", fps, timewaster_delay+G_DELAY);

                /* do program logic */
                do_prog();
                x+=dx;y+=dy;
                if (x>151 || x<0) dx=-dx;
                if (y>150 || y<0) dy=-dy;
        
                if (ticks==0)
                {
                        /* draw graphics */
                        clear(osb);
                        circle(osb, x, y, 10, 128);
                        rest(G_DELAY); /* an extra pretend delay for the graphics */    
                        /* control timing */
                        while (ticks<1)
                        {  
                                yield_timeslice();
                        }
                        blit(osb, screen, 0, 0, (SCREEN_W-osb->w)/2, (SCREEN_H-osb->h)/2, osb->w, osb->h);
                }
                --ticks;
                ++frames;
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
                        ++timewaster_delay;
                        if (timewaster_delay>200) timewaster_delay=0;
                        in_k=1;
                }
                if (key[KEY_MINUS_PAD]) 
                {
                        --timewaster_delay;
                        if (timewaster_delay<0) timewaster_delay=200;
                        in_k=1;
                }
}

