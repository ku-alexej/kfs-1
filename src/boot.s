/* 
 * Assembly boot code that creates the Multiboot header,
 * initializes the CPU state, sets up a kernel stack,
 * and calls the C kernel_main function.
 */

/* 
 * Set assembler syntax to Intel (destination first: `mov dest, src`),
 * without requiring % for registers
 */
.intel_syntax noprefix

/* --- MULTIBOOT HEADER SECTION --- */
.section .multiboot                 /* Put this code into the .multiboot section (matched by the linker script) */
.align 4                            /* Align the header on a 4-byte boundary for GRUB to read it properly */
.long 0x1BADB002                    /* Magic number identifying this binary as Multiboot-compliant */
.long 0x00000000                    /* Flags: set to 0 (no optional Multiboot features requested) */
.long -(0x1BADB002 + 0x00000000)    /* Checksum: magic + flags + checksum must equal 0 */

/* --- BSS SECTION (STACK SETUP) --- */
.section .bss                       /* Put this block in uninitialized RAM */
.align 16                           /* Align the stack memory on a 16-byte boundary (x86 standard) */
stack_bottom:                       /* Label marking the start (bottom/lowest memory address) of the stack */
.skip 16384                         /* Reserve 16384 bytes (16 KiB) of zeroed memory for the stack */
stack_top:                          /* Label marking the end/top of the stack (stack grows downward toward bottom) */

/* --- TEXT SECTION (EXECUTABLE CODE) --- */
.section .text                      /* Put executable code into the .text section */
.code32                             /* Tell GNU Assembler to generate 32-bit x86 instructions */
.globl _start                       /* Make the `_start` symbol visible globally to the linker */
.type _start, @function             /* Mark `_start` as a function for ELF tools */
.extern kernel_main                 /* Declare that `kernel_main` is defined in another file (C code) */

_start:                             /* The main entry point where GRUB jumps after loading the binary */
    cli                             /* Clear Interrupt Flag: disable CPU interrupts until system IDT is built */
    mov esp, offset stack_top       /* Load the address of `stack_top` into Stack Pointer (ESP) */
    xor ebp, ebp                    /* Clear Base Pointer (EBP = 0) to mark the end of the stack frame backtrace */

    push ebx                        /* Push 2nd parameter: address of Multiboot Info structure */
    push eax                        /* Push 1st parameter: Multiboot magic value */
    call kernel_main                /* Transfer control to C function `kernel_main(magic, info)` */

.hang:                              /* Infinite fallback loop if `kernel_main` ever unexpectedly returns */
    cli                             /* Ensure interrupts stay disabled */
    hlt                             /* Halt CPU execution until the next interrupt (saves host CPU power) */
    jmp .hang                       /* Loop back to halt again if a non-maskable interrupt wakes the CPU */

.size _start, . - _start            /* Calculate and record the total size of the `_start` symbol */

.att_syntax prefix                  /* Switch back to default AT&T syntax mode */
