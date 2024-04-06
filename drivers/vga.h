#ifndef VGA_H
#define VGA_H

#include "kernellib/string.h"
#include "kernellib/ascii.h"

#define DEFAULT_VGA_COLOR   0x00000007
#define VGA_MEM_START       0x000B8000
#define VGA_SCREEN_WIDTH    80
#define VGA_SCREEN_HEIGHT   25
#define VGA_SCREEN_DEPTH    2
#define VGA_SCREEN          VGA_SCREEN_WIDTH*VGA_SCREEN_DEPTH*VGA_SCREEN_HEIGHT

extern char *glob_vidptr;
extern unsigned int glob_vga_color;

void setGlobVidPtr(unsigned int location_index);
unsigned int getLineNumber();
void setVGAColor(unsigned int vga_color);
void print(const char *string);
void clrscr();

#endif
