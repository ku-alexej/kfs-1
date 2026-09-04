#ifndef PRINTK_H
#define PRINTK_H

/*
 * Supported format specifiers:
 *   %c  character
 *   %s  string
 *   %d  signed decimal integer
 *   %u  unsigned decimal integer
 *   %x  unsigned hexadecimal integer: 0x12A3
 *   %%  literal '%'
 */
void printk(const char *format, ...);

#endif
