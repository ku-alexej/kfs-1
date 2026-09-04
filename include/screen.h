#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

// Number of text columns in the VGA display.
#define VGA_WIDTH  80u
// Number of text rows in the VGA display.
#define VGA_HEIGHT 25u

// Physical address of the VGA text-mode video memory.
// (colors are stored in the upper byte, 
// characters in the lower byte)
// example: VGA_MEMORY[0] = 0x0741;
//     0x41 = 'A'
//     0x07 = light grey on black background
#define VGA_MEMORY 0xB8000u

// VGA CRT Controller index/command I/O port.
// (used to select the register to access)
#define VGA_CRTC_COMMAND 0x3D4u
// VGA CRT Controller data I/O port.
// (used to read/write the selected register)
#define VGA_CRTC_DATA    0x3D5u

// CRT Controller register index for the cursor start scanline.
#define VGA_CURSOR_HIGH  0x0Eu
// CRT Controller register index for the cursor end scanline.
#define VGA_CURSOR_LOW   0x0Fu

// CRT Controller register index for cursor start and visibility settings.
#define VGA_CURSOR_START 0x0Au
// CRT Controller register index for cursor end and visibility settings.
#define VGA_CURSOR_END   0x0Bu

typedef enum screen_color
{
    SCREEN_BLACK = 0,
    SCREEN_BLUE = 1,
    SCREEN_GREEN = 2,
    SCREEN_CYAN = 3,
    SCREEN_RED = 4,
    SCREEN_MAGENTA = 5,
    SCREEN_BROWN = 6,
    SCREEN_LIGHT_GREY = 7,
    SCREEN_DARK_GREY = 8,
    SCREEN_LIGHT_BLUE = 9,
    SCREEN_LIGHT_GREEN = 10,
    SCREEN_LIGHT_CYAN = 11,
    SCREEN_LIGHT_RED = 12,
    SCREEN_LIGHT_MAGENTA = 13,
    SCREEN_YELLOW = 14,
    SCREEN_WHITE = 15
} screen_color_t;

#define SCREEN_ATTRIBUTE(fground, bground) ((unsigned char)(((bground) << 4) | (fground)))
#define VGA_DEFAULT_COLOR SCREEN_ATTRIBUTE(SCREEN_LIGHT_GREY, SCREEN_BLACK)

/* Some basic code to print some stuff on the screen */
void screen_clear(void);
void screen_set_color(unsigned char color);
void screen_put_char(char c);
void screen_put_string(const char *s);
void screen_put_line(const char *s);
void screen_set_cursor(size_t x, size_t y);

#endif
