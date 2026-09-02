#include "kernel.h"
#include "multiboot.h"
#include "screen.h"

// Main function of the kernel
void kernel_main(unsigned int multiboot_magic, unsigned int multiboot_info_address)
{
    (void)multiboot_info_address;

    screen_clear();

    if (multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        screen_put_line("KFS_1: invalid Multiboot magic");
        return;
    }

	screen_put_line("42");

	for (int i = 1; i < 23; i++)
	{
		screen_put_line("--------------------------------");
	}
}
