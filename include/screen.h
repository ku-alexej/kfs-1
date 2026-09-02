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
#define VGA_MEMORY 0xB8000u
// Default character attribute: bright white foreground on a black background.
#define VGA_COLOR  0x0Fu

// VGA CRT Controller index/command I/O port.
#define VGA_CRTC_COMMAND 0x3D4u
// VGA CRT Controller data I/O port.
#define VGA_CRTC_DATA    0x3D5u
// CRT Controller register index for the cursor start scanline.
#define VGA_CURSOR_HIGH  0x0Eu
// CRT Controller register index for the cursor end scanline.
#define VGA_CURSOR_LOW   0x0Fu
// CRT Controller register index for cursor start and visibility settings.
#define VGA_CURSOR_START 0x0Au
// CRT Controller register index for cursor end and visibility settings.
#define VGA_CURSOR_END   0x0Bu

/* Some basic code to print some stuff on the screen */
void screen_clear(void);
void screen_put_char(char c);
void screen_put_string(const char *s);
void screen_put_line(const char *s);
void screen_set_cursor(size_t x, size_t y);

#endif
