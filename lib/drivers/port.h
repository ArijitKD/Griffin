#ifndef PORT_H
#define PORT_H

#include "types.h"

/*
static inline uint8 inportb (uint16 port)
{
    uint8 value;
    asm volatile ("inb %1, %0": "=a" (value) : "Nd" (port));
    return value;
}

static inline void outportb (uint16 port, uint8 value)
{
    asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}
*/

int8 inportb (uint16 port)
{
    uint8 data;
    __asm__("in %%dx, %%al": "=a" (data) : "d" (port));
    return data;
}

void outportb (uint16 port, uint8 data)
{
    __asm__("out %%al, %%dx" : : "d" (port), "a" (data));
}

#endif