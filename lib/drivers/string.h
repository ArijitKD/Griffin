#ifndef STRING_H
#define STRING_H

#include "types.h"

// Special characters that cannot be typed from keyboard
#define NULL                0x00
#define BACKSPACE           0x08
#define TABSPACE            0x09
#define NEWLINE             0x0A
#define CARRIAGE_RETURN     0x0D


uint16 strlen(const char* string)
{
    uint16 i=0;
    while (string[i++]);
    return i-1;
}

char* strcopy(char* dest, const char* src)
{
    uint16 i=0, j=0;
    uint16 length = strlen(src);
    dest = NULL;

    while (i<length)
    {
        dest[i] = src[i];
        i++;
    }
    
    dest[i] = NULL;
    return dest; 
}

char* reverse(const char* string)
{
    uint16 length = strlen(string);
    char* finalstr;
    finalstr = strcopy(finalstr, string);
    uint16 i=0;
    while (i<length)
    {
        finalstr[i] = string[length-i-1];
        i++;
    }
    return finalstr;
}

char* concat(char* str1, const char* str2)
{
    uint16 i=0, j=0;
    uint16 length = strlen(str1);
    uint16 total_length = length + strlen(str2);

    char* finalstr;
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