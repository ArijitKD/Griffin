#ifndef VGA_H
#define VGA_H

// Screen dimensions in VGA mode
#define SCREEN_WIDTH           80
#define SCREEN_HEIGHT          25
#define SCREEN_DEPTH           2

// Start address of video memory in VGA mode
#define VIDMEM_START_ADDR      0xB8000

#define DEFAULT                0x07     // Default text color
#define ERROR                  0x0C     // Default text color for errors

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

#endif