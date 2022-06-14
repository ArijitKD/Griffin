#ifndef VGA_H
#define VGA_H

#include "types.h"
#include "string.h"
#include "sysio.h"


// Screen dimensions in VGA mode
#define SCREEN_WIDTH           80
#define SCREEN_HEIGHT          25
#define SCREEN_DEPTH           2

// Start address of video memory in VGA mode
#define VIDMEM_START_ADDR      0xB8000

#define DEFAULT                0x07     // Default text color
#define ERROR                  0x0C     // Default text color for errors

// 16 Colors in VGA mode
#define BLACK                  0x00
#define BLUE                   0x01
#define GREEN                  0x02
#define TEAL                   0x03
#define RED                    0x04
#define PURPLE                 0x05
#define ORANGE                 0x06
#define LIGHTGRAY              0x07
#define GRAY                   0x08
#define ROYALBLUE              0x09
#define LIGHTGREEN             0x0A
#define AQUA                   0x0B
#define CRIMSON                0x0C
#define PINK                   0x0D
#define YELLOW                 0x0E
#define WHITE                  0x0F


DWORD xcursor = 0, ycursor = 0;

void clrline (UBYTE from, UBYTE to)
{
    CHRPTR vidmem = (CHRPTR)VIDMEM_START_ADDR;
    UWORD i = SCREEN_WIDTH * SCREEN_DEPTH * from;

    while (i<(SCREEN_WIDTH * SCREEN_DEPTH * (to+1)))
    {
        vidmem[i++] = NULL;
    }
}

void updatecursor()
{
    UDWORD temp = ycursor * SCREEN_WIDTH + xcursor;
    outportb (0x3D4, 14);
    outportb (0x3D5, temp >> 8);
    outportb (0x3D4, 15);
    outportb (0x3D5, temp);

}

void clrscr()
{
    clrline (0, SCREEN_HEIGHT-1);
    xcursor = 0;
    ycursor = 0;
    updatecursor();
}

void upscroll (UBYTE line)
{
    CHRPTR vidmem = (CHRPTR)VIDMEM_START_ADDR;
    UWORD i=0;

    while (i<(SCREEN_WIDTH * SCREEN_DEPTH * (SCREEN_HEIGHT-1)))
    {
        vidmem[i] = vidmem[SCREEN_WIDTH * SCREEN_DEPTH * line + i];
        i++;
    }
    clrline ((SCREEN_HEIGHT-1)-line, SCREEN_HEIGHT-1);

    if ((ycursor-line) < 0)
        xcursor = ycursor = 0;
    else
        ycursor -= line;

    updatecursor();
}

void putchar (UBYTE ch, UBYTE color)
{
    CHRPTR vidmem = (CHRPTR)VIDMEM_START_ADDR;

    switch (ch)
    {
        case BACKSPACE:
                                if (xcursor > 0)
                                {
                                    xcursor--;
                                    vidmem[(ycursor * SCREEN_WIDTH + xcursor) * SCREEN_DEPTH] = NULL;
                                }
                                break;
        
        case TABSPACE:
                                xcursor = (xcursor+8) & ~(8-1);
                                break;
        
        case NEWLINE:
                                xcursor = 0;
                                ycursor++;
                                break;

        case CARRIAGE_RETURN:
                                xcursor = 0;
                                break;

        default:
                                vidmem[(ycursor * SCREEN_WIDTH + xcursor) * SCREEN_DEPTH] = ch;
                                vidmem[((ycursor * SCREEN_WIDTH + xcursor) * SCREEN_DEPTH) + 1] = color;
                                xcursor++;
                                break;
                                
    }
    
    if (xcursor >= SCREEN_WIDTH)
    {
        xcursor = 0;
        ycursor++;
    }

    if (ycursor >= SCREEN_HEIGHT-1)
    {
        upscroll(1);
    }
    updatecursor();
}

void print (CHRPTR string, UBYTE color)
{
    UWORD i = 0;
    UWORD length = strlen(string);

    while (i<length)
    {
        putchar (string[i++], color);
    }
}

#endif