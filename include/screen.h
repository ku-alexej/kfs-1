#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

#define VGA_WIDTH  80u
#define VGA_HEIGHT 25u
#define VGA_MEMORY 0xB8000u
#define VGA_COLOR  0x0Fu    // white on black

/* Some basic code to print some stuff on the screen */

void screen_clear(void);
void screen_put_char(char c);
void screen_put_string(const char *s);
void screen_put_line(const char *s);
void screen_set_cursor(size_t x, size_t y);

#endif
