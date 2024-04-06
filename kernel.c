#include "drivers/vga.h"
#include "drivers/kernellib/string.h"

void kmain()
{
  //setVGAColor(DEFAULT_VGA_COLOR);
  clrscr();
  print ("Griffin OS [build: 0.0.0_pre-alpha]\nCopyright (c) Arijit Kumar Das (Github: @ArijitKD). By using this software, you agree to the terms of the GNU GPL v3.0.\n\nWelcome to Griffin OS. To get started, type a command.\n\nGRIFFIN> ");
  setVGAColor(0x0A);
}