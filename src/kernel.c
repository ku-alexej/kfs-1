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

	screen_put_line("KFS_1: Hello, World!");
	screen_put_line("99 bottles of beer on the wall, 99 bottles of beer.");
	screen_put_line("Take one down and pass it around, 98 bottles of beer on the wall.");
	screen_put_line("98 bottles of beer on the wall, 98 bottles of beer.");
	screen_put_line("Take one down and pass it around, 97 bottles of beer on the wall.");
	screen_put_line("97 bottles of beer on the wall, 97 bottles of beer.");
	screen_put_line("Take one down and pass it around, 96 bottles of beer on the wall.");
	screen_put_line("96 bottles of beer on the wall, 96 bottles of beer.");
	screen_put_line("Take one down and pass it around, 95 bottles of beer on the wall.");
	screen_put_line("95 bottles of beer on the wall, 95 bottles of beer.");
	screen_put_line("Take one down and pass it around, 94 bottles of beer on the wall.");
	screen_put_line("94 bottles of beer on the wall, 94 bottles of beer.");
	screen_put_line("Take one down and pass it around, 93 bottles of beer on the wall.");
	screen_put_line("93 bottles of beer on the wall, 93 bottles of beer.");
	screen_put_line("Take one down and pass it around, 92 bottles of beer on the wall.");
	screen_put_line("92 bottles of beer on the wall, 92 bottles of beer.");
	screen_put_line("...");
	screen_put_line("Superlong line that should wrap around the screen and continue on the next line, but it doesn't because we haven't implemented line wrapping yet.");
	screen_put_line(".\n.\n.");
	screen_put_line(".\n.\n.");
	screen_put_line(".\n.\n.");
	screen_put_line(".\n.\n.");
	screen_put_line(".\n.\n.");
	screen_put_line(".\n.\n.");
	screen_put_line(".\n.\n.");
	screen_put_line(".\n.\n.");
	screen_put_line(".\n.\n.");
	
}
