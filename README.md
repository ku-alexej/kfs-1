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
