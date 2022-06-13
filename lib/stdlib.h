#ifndef STDLIB_H
#define STDLIB_H

#include "types.h"
#include "string.h"
#include "drivers/sysio.h"
#include "vga.h"

#define NULL                0x00
#define BACKSPACE           0x08
#define TABSPACE            0x09
#define NEWLINE             0x0A
#define CARRIAGE_RETURN     0x0D


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