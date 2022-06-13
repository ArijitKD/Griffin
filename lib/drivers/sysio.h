#ifndef SYSIO_H
#define SYSIO_H

#include "types.h"

UBYTE inportb (UWORD port)
{
    UBYTE readch;
    __asm__ __volatile__ ("inb %1, %0": "=a" (readch) : "dN" (port));
    return readch;
}

void outportb (UWORD port, UBYTE data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

#endif