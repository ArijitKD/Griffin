#include "lib/stdlib.h"

#define KERNEL_VERSION      "1.0.1_pre-alpha"
#define PROMPT              "octuron>"
#define CREATOR             "Arijit Kumar Das"

void kmain()
{
    clrscr();

    print (concat("Octuron ", "OS "), YELLOW);
    print (KERNEL_VERSION, AQUA);
    print ("\n\n", DEFAULT);
    print ("Hello there!!! This is Octuron, an OS kernel designed by ", ROYALBLUE);
    print (CREATOR, PINK);
    print ("\n\n", DEFAULT);
    print ("Do you like this kernel? Let us know :D\n\n", LIGHTGREEN);

    for (UBYTE i=0; i<SCREEN_WIDTH; i++)
    {
        putchar ('=', PURPLE);
    }
    print (PROMPT, TEAL);
}