#include "vga.h"

char *glob_vidptr = (char*)VGA_MEM_START;
unsigned int glob_vga_color = DEFAULT_VGA_COLOR;

void setGlobVidPtr(unsigned int location_index)
{
  if (location_index<0)
    location_index = 0;
  else if (location_index>VGA_SCREEN)
    location_index = VGA_SCREEN;
  glob_vidptr = (char*)(VGA_MEM_START+location_index);
}

unsigned int getLineNumber()
{
  unsigned int i, location_index = (unsigned int)glob_vidptr-VGA_MEM_START;
  for (i=0; i<VGA_SCREEN_HEIGHT; i++)
  {
    if (location_index>=(VGA_SCREEN_WIDTH*VGA_SCREEN_DEPTH*i) && location_index<(VGA_SCREEN_WIDTH*VGA_SCREEN_DEPTH*(i+1)))
      break;
  }
  return i;
}

void setVGAColor(unsigned int vga_color)
{
  char *glob_vidptr_position = glob_vidptr;
  glob_vga_color = vga_color;
  setGlobVidPtr(0);
  unsigned int i;
  for (i=1; i<VGA_SCREEN; i+=2)
  {
    glob_vidptr[i] = glob_vga_color;
  }
  glob_vidptr = glob_vidptr_position;
}

void print(const char *string)
{
  unsigned int i, j;
  unsigned int length = strlength(string);
  for (i=j=0; i<length; i++,j+=2)
  {

    if (string[i] == LINE_FEED)
    {
      /*
      while (j%(VGA_SCREEN_WIDTH*VGA_SCREEN_DEPTH)!=0)
      {
        //glob_vidptr[j] = 0;
        glob_vidptr[j+1] = glob_vga_color;
        j+=2;
      }
      j-=2;
      */
      setGlobVidPtr(VGA_SCREEN_WIDTH*VGA_SCREEN_DEPTH*(getLineNumber()+1));
      j=-2;
      while (glob_vidptr[j] != 0)
      {
        setGlobVidPtr(VGA_SCREEN_WIDTH*VGA_SCREEN_DEPTH*(getLineNumber()+1));
      }
    }
    else if (string[i] == CARRIAGE_RETURN)
    {
      setGlobVidPtr(VGA_SCREEN_WIDTH*VGA_SCREEN_DEPTH*getLineNumber());
      j=-2;
    }
    else
    {
      glob_vidptr[j] = string[i];
      glob_vidptr[j+1] = glob_vga_color;
    }  
  }
  //glob_vidptr += j;
  setGlobVidPtr(((unsigned int)glob_vidptr-VGA_MEM_START)+j);
}

void clrscr()
{
  setGlobVidPtr(0);
  for (unsigned int i=0; i<=VGA_SCREEN; i+=2)
  {
    glob_vidptr[i] = 0;
    glob_vidptr[i+1] = glob_vga_color;
  }
  setGlobVidPtr(0);
}
