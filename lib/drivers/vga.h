#ifndef VGA_H
#define VGA_H

#include "types.h"
#include "string.h"
#include "port.h"


// Screen dimensions in VGA mode
#define SCREEN_WIDTH           80
#define SCREEN_HEIGHT          25
#define SCREEN_DEPTH           2

// Start address of video memory in VGA mode
#define VIDMEM_START_ADDR      0xB8000

#define VGA_CTRL_REGISTER      0x3D4
#define VGA_DATA_REGISTER      0x3D5
#define VGA_OFFSET_LOW         15
#define VGA_OFFSET_HIGH        14

#ifndef VGA_PROMPT
#define VGA_PROMPT  "griffin>"
#endif

#ifndef DEFAULT_TEXT_COLOR
#define DEFAULT_TEXT_COLOR     0x07
#endif

/*
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
*/


char* prompt = VGA_PROMPT;
uint32 xcursor = 0, ycursor = 0;

uint32 getcursor()
{
    outportb (VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int32 offset = inportb (VGA_DATA_REGISTER) << 8;

    outportb (VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += inportb (VGA_DATA_REGISTER);

    return offset;
}

void setcursor (int offset)
{
    outportb (VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    outportb (VGA_DATA_REGISTER, (uint8)(offset >> 8));

    outportb (VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    outportb (VGA_DATA_REGISTER, (uint8)(offset & 0xFF));
}

void set_block_type_cursor(bool yes)
{
    if (yes)
    {
        outportb (VGA_CTRL_REGISTER, 0x0A);
        outportb (VGA_DATA_REGISTER, (inportb(VGA_DATA_REGISTER) & 0xC0) | 0);

        outportb (VGA_CTRL_REGISTER, 0x0B);
        outportb (VGA_DATA_REGISTER, (inportb(VGA_DATA_REGISTER) & 0xE0) | 15);
    }
    else
    {
        //print ("insert2", DEFAULT_TEXT_COLOR) ;
    }

}

void clrline (uint8 from, uint8 to)
{
    char* vidmem = (char*)VIDMEM_START_ADDR;
    uint16 i = SCREEN_WIDTH * SCREEN_DEPTH * from;

    while (i<(SCREEN_WIDTH * SCREEN_DEPTH * (to+1)))
    {
        vidmem[i] = NULL;
        vidmem[i+1] = DEFAULT_TEXT_COLOR;
        i+=2;
    }
}

/*
void updatecursor()
{
    uint32 temp = ycursor * SCREEN_WIDTH + xcursor;
    outportb (0x3D4, 14);
    outportb (0x3D5, (temp >> 8));
    outportb (0x3D4, 15);
    outportb (0x3D5, (temp & 0xff));

}
*/

void clrscr()
{
    clrline (0, SCREEN_HEIGHT-1);
    xcursor = ycursor = 0;
    setcursor(0);
}

void upscroll (uint8 line)
{
    char* vidmem = (char*)VIDMEM_START_ADDR;
    uint16 i=0;

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

    setcursor(getcursor());
}

void putchar (const char ch)
{
    char* vidmem = (char*)VIDMEM_START_ADDR;

    switch (ch)
    {
        case BACKSPACE:
                                if (xcursor > strlen(prompt))
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
                                vidmem[((ycursor * SCREEN_WIDTH + xcursor) * SCREEN_DEPTH) + 1] ;
                                xcursor++;
                                break;
                                
    }
    
    if (xcursor >= SCREEN_WIDTH)
    {
        xcursor = 0;
        ycursor++;
        prompt = "";
    }

    if (ycursor >= SCREEN_HEIGHT-1)
    {
        upscroll(1);
    }
    setcursor(ycursor * SCREEN_WIDTH + xcursor);;
}

void print (const char* string)
{
    uint16 i = 0;
    uint16 length = strlen(string);

    while (i<length)
    {
        putchar (string[i++]);
    }
}

void init_vga()
{
    print (concat(concat(concat(OS_NAME, " (Version: "), KERNEL_VERSION),")\n"));
    print (concat(COPYRIGHT, "\n\n"));
    print (concat("Initialize VGA driver:"," [  OK  ]\n"));
}

#endif