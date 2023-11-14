#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Custom printf function.
 * @format: Format string.
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    while (*format)
    {
        if (*format == '%' && (*(format + 1) == 'c' || *(format + 1) == 's' || *(format + 1) == '%'))
        {
            format++; // Move past '%'

            switch (*format)
            {
            case 'c':
                count += write(1, va_arg(args, int), 1);
                break;
            case 's':
                count += write(1, va_arg(args, char *), 0);
                break;
            case '%':
                count += write(1, "%", 1);
                break;
            }
        }
        else
        {
            count += write(1, format, 1);
        }

        format++;
    }

    va_end(args);

    return count;
}

