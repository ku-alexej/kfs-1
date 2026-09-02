#include "screen.h"

/* Some basic code to print some stuff on the screen */

static volatile unsigned short *const vga = (volatile unsigned short *)VGA_MEMORY;
static size_t cursor_x = 0;
static size_t cursor_y = 0;

static unsigned short vga_entry(unsigned char c)
{
    return (unsigned short)c | ((unsigned short)VGA_COLOR << 8);
}

static void vga_outb(unsigned short port, unsigned char value)
{
    __asm__ volatile (
        ".intel_syntax noprefix\n"
        "out dx, al\n"
        ".att_syntax prefix\n"
        :
        : "d"(port), "a"(value)
    );
}

static void screen_enable_cursor(void)
{
    vga_outb(VGA_CRTC_COMMAND, VGA_CURSOR_START);
    vga_outb(VGA_CRTC_DATA, 0u);

    vga_outb(VGA_CRTC_COMMAND, VGA_CURSOR_END);
    vga_outb(VGA_CRTC_DATA, 15u);
}

static void screen_update_cursor(void)
{
    unsigned short position = (unsigned short)(cursor_y * VGA_WIDTH + cursor_x);

    vga_outb(VGA_CRTC_COMMAND, VGA_CURSOR_LOW);
    vga_outb(VGA_CRTC_DATA, (unsigned char)(position & 0xFFu));

    vga_outb(VGA_CRTC_COMMAND, VGA_CURSOR_HIGH);
    vga_outb(VGA_CRTC_DATA, (unsigned char)((position >> 8) & 0xFFu));
}

static void screen_scroll(void)
{
    size_t y;
    size_t x;

	/* Scroll the screen up by one row. */
    for (y = 1; y < VGA_HEIGHT; ++y)
        for (x = 0; x < VGA_WIDTH; ++x)
            vga[(y - 1u) * VGA_WIDTH + x] = vga[y * VGA_WIDTH + x];

    /* Clear the last row. */
    for (x = 0; x < VGA_WIDTH; ++x)
        vga[(VGA_HEIGHT - 1u) * VGA_WIDTH + x] = vga_entry(' ');

    /* Continue writing on the last visible row. */
    cursor_y = VGA_HEIGHT - 1u;
}

void screen_set_cursor(size_t x, size_t y)
{
    cursor_x = x % VGA_WIDTH;
    cursor_y = y % VGA_HEIGHT;

    screen_update_cursor();
}

void screen_clear(void)
{
    size_t y;
    size_t x;

    for (y = 0; y < VGA_HEIGHT; ++y)
        for (x = 0; x < VGA_WIDTH; ++x)
            vga[y * VGA_WIDTH + x] = vga_entry(' ');

    screen_set_cursor(0, 0);
	screen_enable_cursor();
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
        screen_scroll();

	screen_update_cursor();
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
