#include "types.h"
#include "screen.h"

#define  va_start(ap, last) __builtin_va_start(ap, last)
#define  va_arg(ap, type)   __builtin_va_arg(ap, type)
#define  va_end(ap)         __builtin_va_end(ap)

static void printk_unsigned(unsigned int value, unsigned int base)
{
    char digits[] = "0123456789ABCDEF";
    char buffer[8];
    size_t i;

    if (value == 0u)
    {
        screen_put_char('0');
        return;
    }

    i = 0;
    while (value != 0u)
    {
        buffer[i] = digits[value % base];
        i++;
        value /= base;
    }

    while (i > 0u)
    {
        i--;
        screen_put_char(buffer[i]);
    }
}

static void printk_signed(int n)
{
    unsigned int number;

    if (n < 0)
    {
        screen_put_char('-');
        number = (unsigned int)(-(n + 1)) + 1u;
    }
    else
    {
        number = (unsigned int)n;
    }

    printk_unsigned(number, 10u);
}

static void printk_format(const char *str, va_list *args)
{
    while (*str != '\0')
    {
		// regular characters
        if (*str != '%')
        {
            screen_put_char(*str);
            str++;
            continue;
        }
        str++;

		// '%' as a final character
        if (*str == '\0')
        {
            screen_put_char('%');
            break;
        }

		// '%' or arguments according the formst
		if (*str == '%')
			screen_put_char('%');
		else if (*str == 'c')
			screen_put_char((char)va_arg(*args, int));
		else if (*str == 's')
		{
			const char *s = va_arg(*args, const char *);
			if (s == (const char *)0)
				s = "(null)";
			screen_put_string(s);
		}
		else if (*str == 'd')
			printk_signed(va_arg(*args, int));
		else if (*str == 'u')
			printk_unsigned(va_arg(*args, unsigned int), 10u);
		else if (*str == 'x')
		{
			screen_put_string("0x");
			printk_unsigned(va_arg(*args, unsigned int), 16u);
		}
		else
		{
			screen_put_char('%');
			screen_put_char(*str);
		}

		// to the next char in te string and new loop
        str++;
    }
}

void printk(const char *str, ...)
{
    va_list args;

    va_start(args, str);
    printk_format(str, &args);
    va_end(args);
}
