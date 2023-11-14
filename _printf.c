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
        if (*format == '%' && *(format + 1) != '\0')
        {
            format++; // Move past '%'
            switch (*format)
            {
                case 'c':
                    count += write(1, &va_arg(args, int), 1);
                    break;
                case 's':
                    count += write(1, va_arg(args, char *), 1);
                    break;
                case '%':
                    count += write(1, "%", 1);
                    break;
                default:
                    count += write(1, "%", 1);
                    count += write(1, format, 1);
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

int main(void)
{
    _printf("I'm not going anywhere. You can print that wherever you want to. I'm here and I'm a Spur for life\n");
    return (0);
}

