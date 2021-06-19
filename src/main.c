#include <stdio.h>
#include <dos.h>
#include <time.h>

#define VIDEO_INT           0x10      /* the BIOS video interrupt. */
#define VGA_256_COLOR_MODE  0x13      /* use to set 256-color mode. */
#define TEXT_MODE           0x03      /* use to set 80x25 text mode. */

#define SCREEN_WIDTH        320       /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT       200       /* height in pixels of mode 0x13 */
#define NUM_COLORS          256       /* number of colors in mode 0x13 */



typedef unsigned char  byte;
typedef unsigned short word;


byte far *VGA = (byte far*)0xA0000000L; /* Video memory */
                                        
enum COLORS {
    COLOR_BLACK = 0,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_LIGHT_GRAY,
    COLOR_DARK_GRAY,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_CYAN,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_MAGENTA,
    COLOR_YELLOW,
    COLOR_WHITE,
};


void set_video_mode(byte mode)
{
    union REGS regs;       
    
    regs.h.ah = 0x00;
    regs.h.al = mode;
    
    int86(VIDEO_INT, &regs, &regs);
}


void plot_pixel(short x, short y, byte color)
{

    union  REGS regs;

    regs.h.ah = 0x0C;
    regs.h.al = color;
    regs.x.cx = x;
    regs.x.dx = y;

    int86(VIDEO_INT, &regs, &regs);

}

void fast_plot_pixel(short x, short y, byte color)
{

    VGA[320*y + x] = color;
}


void faster_plot_pixel(short x, short y, byte color)
{

    VGA[(y<<8) + (y << 6)  + x] = color;
}

void plot_line(float a, float b)
{
    short x = 0, y = 0;
    for (x=0; x<SCREEN_WIDTH; x++)
    {
        y = (short) (a*x + b);

        if (y < SCREEN_HEIGHT)
            plot_pixel(x, y, 1);
    }
}

void fast_plot_line(float a, float b)
{
    short x = 0, y = 0;
    for (x=0; x<SCREEN_WIDTH; x++)
    {
        y = (short) (a*x + b);

        if (y < SCREEN_HEIGHT)
            plot_pixel(x, y, 1);
    }
}

void main()
{

    word i;
    short x=0, y=0;
    byte color;
    clock_t start; 
    double t1, t2, t3;


    union REGS regs;

    srand(clock()); // Seed random number generator

    
    // Set video mode to 0x13 (256 Color 320x240)
    set_video_mode(VGA_256_COLOR_MODE);

    printf("Using the slow mode\n");

    start = clock();
    for (i=0; i<50000L; i++) 
    {
        x = rand() % SCREEN_WIDTH;
        y = rand() % SCREEN_WIDTH;
        color = rand() % 16; 

        plot_pixel(x, y, color);
    }

    t1 = (double) (clock() - start)/CLOCKS_PER_SEC/1000;

    printf("Using the fast mode:\n");

    start = clock();
    for (i=0; i<50000L; i++) 
    {
        x = rand() % SCREEN_WIDTH;
        y = rand() % SCREEN_WIDTH;
        color = rand() % 16; 

        fast_plot_pixel(x, y, color);
    }

    t2 = (double) (clock() - start)/CLOCKS_PER_SEC/1000;

    printf("Using the faster mode:\n");

    start = clock();
    for (i=0; i<50000L; i++) 
    {
        x = rand() % SCREEN_WIDTH;
        y = rand() % SCREEN_WIDTH;
        color = rand() % 16; 

        faster_plot_pixel(x, y, color);
    }

    t3 = (double) (clock() - start)/CLOCKS_PER_SEC/1000;    

    printf("Slow: %fs\nFast: %fs\nFaster: %fs\n", t1, t2, t3);

    if (t2 != 0.0) {
        printf("Fast/Slow: %f\n", t1/t2);
    }

    if (t3 != 0.0) {
        printf("Faster/Fast: %f\n", t2/t3);
    }

    if (t3 != 0.0) {
        printf("Faster/Slow: %f\n", t1/t3);
    }


}