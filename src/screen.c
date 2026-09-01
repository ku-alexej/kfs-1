#include "screen.h"

/* Some basic code to print some stuff on the screen */

static volatile unsigned short *const vga = (volatile unsigned short *)VGA_MEMORY;
static size_t cursor_x = 0;
static size_t cursor_y = 0;

static unsigned short vga_entry(unsigned char c)
{
    return (unsigned short)c | ((unsigned short)VGA_COLOR << 8);
}

void screen_set_cursor(size_t x, size_t y)
{
    cursor_x = x % VGA_WIDTH;
    cursor_y = y % VGA_HEIGHT;
}

void screen_clear(void)
{
    size_t y;
    size_t x;

    for (y = 0; y < VGA_HEIGHT; ++y)
    {
        for (x = 0; x < VGA_WIDTH; ++x)
            vga[y * VGA_WIDTH + x] = vga_entry(' ');
    }
    screen_set_cursor(0, 0);
}

void screen_put_char(char c)
{
    if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else
    {
        vga[cursor_y * VGA_WIDTH + cursor_x] = vga_entry((unsigned char)c);
        cursor_x++;
        if (cursor_x >= VGA_WIDTH)
        {
            cursor_x = 0;
            cursor_y++;
        }
    }

    if (cursor_y >= VGA_HEIGHT)
        cursor_y = 0;
}

void screen_put_string(const char *s)
{
    while (*s != '\0')
    {
        screen_put_char(*s);
        s++;
    }
}

void screen_put_line(const char *s)
{
    screen_put_string(s);
    screen_put_char('\n');
}
