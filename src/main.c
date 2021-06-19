#include <stdio.h>
#include <dos.h>

#define VIDEO_INT           0x10      /* the BIOS video interrupt. */
#define VGA_256_COLOR_MODE  0x13      /* use to set 256-color mode. */
#define TEXT_MODE           0x03      /* use to set 80x25 text mode. */

#define SCREEN_WIDTH        320       /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT       200       /* height in pixels of mode 0x13 */
#define NUM_COLORS          256       /* number of colors in mode 0x13 */

typedef unsigned char  byte;
typedef unsigned short word;

void main() {

    int i=0;
    union REGS regs;
    
    regs.h.ah = 0x00;
    regs.h.al = 0x13;
    int86(0x10, &regs, &regs);
    printf("Hello, World!\n");

    regs.h.ah = 0x0C;
    regs.h.al = 0x3;
    
    for(i=0; i<100; i++){
        regs.x.cx = i;
        regs.x.dx = 2*i;
        int86(0x10, &regs, &regs);
    }
    
}