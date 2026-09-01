/* 
 * A linker script tells the compiler/linker EXACTLY where to place 
 * different pieces of compiled C and Assembly code in memory.
 */

/* 
 * Tells the system that the code execution starts at the `_start` label
 * (found in assembly)
 */
ENTRY(_start)

SECTIONS
{
    /* 
     * The BIOS reserves the first 1 MB of RAM for hardware and legacy PC functions, 
     * so custom kernels are almost always loaded starting at 1 MB.
     */
    . = 1M;

    /* Align the next section to a 4-byte boundary (standard 32-bit alignment) */
    . = ALIGN(4);
    /* 
     * Multiboot Header Section
     * The bootloader (our GRUB) looks for this specific header to know 
     * that this file is a bootable kernel.
     */
    .multiboot :
    {
        /* 
         * `KEEP` prevents the linker from accidentally discarding 
         * this section during optimization
         */
        KEEP(*(.multiboot))
    }

    /* Align the next section to a 16-byte boundary for optimized CPU execution */
    . = ALIGN(16);

    /* 
     * Text Section
     * Holds actual executable machine code (functions and instructions).
     */
    .text :
    {
        *(.text)
    }

    /* 
     * Read-Only Data Section
     * Holds constants and string literals.
     * The CPU is not supposed to modify variables in this area.
     */
    .rodata : ALIGN(16)
    {
        *(.rodata)
    }

    /* 
     * Read-Write Data Section
     * Holds global and static variables that have initial values defined (int count = 5;).
     */
    .data : ALIGN(16)
    {
        *(.data)
    }

    /* 
     * BSS Section - Stack / Uninitialized Memory
     * Holds global and static variables that have NOT been initialized (int buffer[1024];).
     * Instead of saving thousands of zeros in the file, this section just tells RAM 
     * how much space to set aside when loaded.
     */
    .bss : ALIGN(16)
    {
        *(COMMON)
        *(.bss)
    }

    /* 
     * Discard Section
     * Throws away compiler-generated extra details (like gcc version comments 
     * and C++ exception unwinding frames).
     */
    /DISCARD/ :
    {
        *(.comment)
        *(.note*)
        *(.eh_frame)
    }
}
