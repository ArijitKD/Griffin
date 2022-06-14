#ifndef STRING_H
#define STRING_H

#include "types.h"

// Special characters that cannot be typed from keyboard
#define NULL                0x00
#define BACKSPACE           0x08
#define TABSPACE            0x09
#define NEWLINE             0x0A
#define CARRIAGE_RETURN     0x0D


UDWORD strlen(CHRPTR string)
{
    DWORD i=0;
    while (string[i++]);
    return i-1;
}

CHRPTR strcopy(CHRPTR dest, const CHRPTR src)
{
    UDWORD i=0, j=0;
    UDWORD length = strlen(src);
    dest = NULL;

    while (i<length)
    {
        dest[i] = src[i];
        i++;
    }
    
    dest[i] = NULL;
    return dest; 
}

CHRPTR concat(CHRPTR str1, const CHRPTR str2)
{
    UDWORD i=0, j=0;
    UDWORD length = strlen(str1);
    UDWORD total_length = length + strlen(str2);

    CHRPTR finalstr;
    finalstr = strcopy(finalstr, str1);

    while (i<=total_length)
    {
        if (i>=length)
        {
            finalstr[i] = str2[j];
            j++;
        }
        i++;
    }
    return finalstr;
}

#endif