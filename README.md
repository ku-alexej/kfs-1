# kfs-1: the first Kernel from Scratch project

## TODO:
0. i386 architecture
1. `GRUB` on an VM

2. `ASM` boot code -> multiboot header + call `kernel` `main()`
3. `kernel` code in `C`
4. An interface between `kernel` and the screen
5. Compilation -> `nasm` + `gcc` + correct flags
6. Custom linker to link compilation results
7. Makefile for ASM + C compilation and linking  

8. Add helpers: kernel types or basic functions (strlen, strcmp, ...)
9. Display "42" on the screen 
10. Size < 10 MB

> QEMU as a HOST VM  
> ASM + C languages

```c
// CPP flags for compilation:

// -fno-builtin
// -fno-exception
// -fno-stack-protector
// -fno-rtti
// -nostdlib
// -nodefaultlibs
```

## Bonus part:

- Scroll and cursor support to I/O interface.
- Colors support to I/O interface.
- Helpers like printf / printk in order to print information / debug easily.
- Handle keyboard entries + print them.
- Handle different screens + keyboard shortcuts to switch between then.

### Scroll

Triggered when `cursor_y >= VGA_HEIGHT`. Shifts all rows up by one position (`n+1 to n`), 
clears the bottom row with space characters, and updates `cursor_y` to point to the last visible line. 
Handled by the `screen_scroll()` function in `screen.c`.

### Cursor

Enabled cursor of block shape, change position of cursor after each new symbol at the screen.

Three function help with that.
1. `vga_outb(port, value)` - used to write a byte (value) to the vga port
3. `screen_enable_block_cursor()` - enable block cursor by using `vga_outb`: sets up start and end
2. `screen_update_cursor()` - changes position of the cursor: sets up low and high bites of the position

```
VGA CRT Controller has two main ports:

0x3D4 - VGA_CRTC_COMMAND - command port to choose VGA register
0x3D5 - VGA_CRTC_DATA    - write data to the chosen VGA register
```

```
Registers that used for this bonus:

0x0Au - VGA_CURSOR_START - where is the start of cursor, the top of it (0..15u)
0x0Bu - VGA_CURSOR_END   - where is the end of cursor, the bottom of it (0..15u)
0x0Eu - VGA_CURSOR_HIGH  - 8 huigh bites of cursor address
0x0Fu - VGA_CURSOR_LOW   - 8 lower bites of cursor address
```

### Colors support

Enable color support for I/O interface. The code in `screen.c` and `screen.h` has features that allow to change background and text color.

1. `screen_set_color(colors)` - used to change current colors for background and text
2. `vga_entry(character)` - prepares 2 bytes (colors + char) for VGA text-mode cell
3. `SCREEN_ATTRIBUTE(text color, background color)` - prepares 1 byte of colors

VGA text-mode cells store next information:

```c
// 16 bits = 2 bytes
// high bytes - color
// low bytes - character

|xxxxxxxx| |xxxxxxxx|
|color   | | char   |
```

The color 1 byte stores data about background and text colors:

```c
// 8 bits = 1 byte 
// high bytes - background color
// low bytes - text color

| xxxx       | | xxxx       |
| background | | text color |
```

Color numbers are defined in `screen.h` as enum. The values are 0..15



## Helpers

Download and extract the grub package locally without sudo:
```bash
mkdir -p "$HOME/.local/grub"
cd "$HOME/.local/grub"

dnf download --destdir . grub2-pc-modules
rpm2cpio grub2-pc-modules-*.rpm | cpio -id
```

Then build and run
```bash
cd /home/akurochk/Documents/kfs-1
make clean
make run GRUB_MODULES="$HOME/.local/grub/usr/lib/grub/i386-pc"
```