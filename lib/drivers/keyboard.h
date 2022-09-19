#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "port.h"
#include "vga.h"


//Row-1 keys
#define ESC         1

#define F1          59
#define F2          60
#define F3          61
#define F4          62

#define F5          63
#define F6          64
#define F7          65
#define F8          66

#define F9          67
#define F10         68
#define F11         87
#define F12         88

#define PRTSCR      55
#define SCROLLK     70


//Row-2 keys
#define BKTICK      41
#define ONE         2
#define TWO         3
#define THREE       4
#define FOUR        5
#define FIVE        6
#define SIX         7
#define SEVEN       8
#define EIGHT       9
#define NINE        10
#define ZERO        11
#define HYPHEN      12
#define EQUAL       13
#define BKSPACE     14

#define INSERT      82
#define HOME        71
#define PAGEUP      73

#define NUMLK       69
#define NUMMINUS    74

//Row-3
#define TAB         15
#define Q           16
#define W           17
#define E           18
#define R           19
#define T           20
#define Y           21
#define U           22
#define I           23
#define O           24
#define P           25
#define SQBRAC1     26
#define SQBRAC2     27
#define BKSLASH     43

#define DELETE      83
#define END         79
#define PAGEDOWN    81

#define NUMPLUS     78


//Row-4
#define CAPSLK      58
#define A           30
#define S           31
#define D           32
#define F           33
#define G           34
#define H           35
#define J           36
#define K           37
#define L           38
#define SEMICOLON   39
#define QUOTE       40
#define ENTER       28

#define CENTER      76


//Row-5
#define LSHIFT      42
#define Z           44
#define X           45
#define C           46
#define V           47
#define B           48
#define N           49
#define M           50
#define COMMA       51
#define DOT         52
#define SLASH       53
#define RSHIFT      54

#define UP          72


//Row-6
#define LCTRL       29
/*#define LWINKEY   */
#define LALT        56
#define SPACE       57
#define RALT        56
/*#define RWINKEY   */
/*#define MENUKEY   */
#define RCTRL       29

#define LEFT        75
#define DOWN        80
#define RIGHT       77

//Key-release
#define K_RELEASE   128


struct KEYDOWN_FLAGS
{
    bool lshift;
    bool rshift;
    bool lalt;
    bool ralt;
    bool rctrl;
    bool lctrl;
};

struct KEYDOWN_FLAGS kdflags = {FALSE};


uint8 getScanCode()
{
    if (inportb(0x64) & 0x1)
    {
        return (inportb(0x60));
    }
    return 0;
}

void flushKey()
{
    uint8 scancode = getScanCode();
    switch (scancode)
    {
        case ONE:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('!');
                    else
                        putchar ('1');
                    break;

        case TWO:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('@');
                    else
                        putchar ('2');
                    break;

        case THREE:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('#');
                    else
                        putchar ('3');
                    break;

        case FOUR:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('$');                   
                    else
                        putchar ('4');
                    break;

        case FIVE:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('%');                   
                    else
                        putchar ('5');
                    break;

        case SIX:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('^');                   
                    else
                        putchar ('6');
                    break;

        case SEVEN:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('&');                   
                    else
                        putchar ('7');
                    break;

        case EIGHT:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('*');                   
                    else
                        putchar ('8');
                    break;

        case NINE:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('(');                   
                    else
                        putchar ('9');
                    break;

        case ZERO:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar (')');                   
                    else
                        putchar ('0');
                    break;

        case HYPHEN:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('_');                   
                    else
                        putchar ('-');
                    break;

        case EQUAL:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('+');                   
                    else
                        putchar ('=');
                    break;

        case BKSPACE:
                    putchar ('\b');
                    break;

        case A:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('A');                   
                    else
                        putchar ('a');
                    break;

        case B:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('B');                   
                    else
                        putchar ('b');
                    break;

        case C:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('C');                   
                    else
                        putchar ('c');
                    break;

        case D:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('D');                   
                    else
                        putchar ('d');
                    break;

        case E:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('E');                   
                    else
                        putchar ('e');
                    break;

        case F:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('F');                   
                    else
                        putchar ('f');
                    break;

        case G:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('G');                   
                    else
                        putchar ('g');
                    break;

        case H:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('H');                   
                    else
                        putchar ('h');
                    break;

        case I:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('I');                   
                    else
                        putchar ('i');
                    break;

        case J:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('J');                   
                    else
                        putchar ('j');
                    break;

        case K:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('K');                   
                    else
                        putchar ('k');
                    break;

        case L:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('L');                   
                    else
                        putchar ('l');
                    break;

        case M:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('M');                   
                    else
                        putchar ('m');
                    break;

        case N:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('N');                   
                    else
                        putchar ('n');
                    break;

        case O:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('O');                   
                    else
                        putchar ('o');
                    break;

        case P:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('P');                   
                    else
                        putchar ('p');
                    break;

        case Q:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('Q');                   
                    else
                        putchar ('q');
                    break;

        case R:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('R');                   
                    else
                        putchar ('r');
                    break;

        case S:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('S');                   
                    else
                        putchar ('s');
                    break;

        case T:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('T');                   
                    else
                        putchar ('t');
                    break;

        case U:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('U');                   
                    else
                        putchar ('u');
                    break;

        case V:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('V');                   
                    else
                        putchar ('v');
                    break;

        case W:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('W');                   
                    else
                        putchar ('w');
                    break;

        case X:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('X');                   
                    else
                        putchar ('x');
                    break;

        case Y:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('Y');                   
                    else
                        putchar ('y');
                    break;

        case Z:
                    if (kdflags.lshift || kdflags.rshift)
                        putchar ('Z');                   
                    else
                        putchar ('z');
                    break;

        case SPACE:
                    putchar (' ');
                    break;

        case LSHIFT:
                    kdflags.lshift = TRUE;
                    flushKey ();
                    break;
        
        case LSHIFT+K_RELEASE:
                    kdflags.lshift = FALSE;
                    flushKey ();
                    break;

        case RSHIFT:
                    kdflags.rshift = TRUE;
                    flushKey ();
                    break;
        
        case RSHIFT+K_RELEASE:
                    kdflags.rshift = FALSE;
                    flushKey ();
                    break;

        case RALT:
                    kdflags.ralt = TRUE;
                    flushKey ();
                    break;

        case RALT+K_RELEASE:
                    kdflags.ralt = FALSE;
                    flushKey ();
                    break;

        case ENTER:
                prompt = VGA_PROMPT;
                print (concat("\n", prompt));
                break;
    }
}

void init_keyboard()
{
    print (concat("Initialize keyboard  ", ": [  OK  ]\n"));
    print (concat("\n", VGA_PROMPT));
    while (TRUE)
    {
        flushKey();
    }
}
#endif