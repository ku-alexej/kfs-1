#include "kernel.h"
#include "multiboot.h"
#include "screen.h"
#include "printk.h"

// Main function of the kernel
void kernel_main(unsigned int multiboot_magic, unsigned int multiboot_info_address)
{
    (void)multiboot_info_address;

    screen_clear();

    if (multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
		screen_set_color(SCREEN_ATTRIBUTE(SCREEN_LIGHT_RED, SCREEN_BLACK));
        screen_put_line("KFS_1: invalid Multiboot magic");
        return;
    }

	screen_set_color(SCREEN_ATTRIBUTE(SCREEN_LIGHT_BLUE, SCREEN_DARK_GREY));
	screen_put_line("42");

	screen_set_color(SCREEN_ATTRIBUTE(SCREEN_YELLOW, SCREEN_BROWN));
	for (int i = 1; i < 23; i++)
	{
		screen_put_line("--------------------------------");
	}
	screen_set_color(VGA_DEFAULT_COLOR);
	printk("my %cittle %s, %d, %u, %x, %%\n", 'l', "fox", -123231, 4200000000, 10);
}
