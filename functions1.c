#include "main.h"

/* Function declarations */
int print_unsigned(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexa(va_list types, char map_to[], char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Array of function pointers */
fmt_t print_unsigned_functions[] = {
    {'u', print_unsigned},
    {'o', print_octal},
    {'x', print_hexadecimal},
    {'X', print_hexa_upper},
    {0, NULL} /* Null terminator for the array */
};

/**
 * print_unsigned - Prints an unsigned number
 */
int print_unsigned(va_list types, char buffer[], int flags, int width, int precision, int size)
{
    unsigned long int num = va_arg(types, unsigned long int);
    num = convert_size_unsgnd(num, size);
    return write_unsgnd(0, num, buffer, flags, width, precision, size);
}

/**
 * print_octal - Prints an unsigned number in octal notation
 */
int print_octal(va_list types, char buffer[], int flags, int width, int precision, int size)
{
    unsigned long int num = va_arg(types, unsigned long int);
    num = convert_size_unsgnd(num, size);
    return write_unsgnd(8, num, buffer, flags, width, precision, size);
}

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 */
int print_hexadecimal(va_list types, char buffer[], int flags, int width, int precision, int size)
{
    return print_hexa(types, "0123456789abcdef", buffer, flags, 'x', width, precision, size);
}

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 */
int print_hexa_upper(va_list types, char buffer[], int flags, int width, int precision, int size)
{
    return print_hexa(types, "0123456789ABCDEF", buffer, flags, 'X', width, precision, size);
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 */
int print_hexa(va_list types, char map_to[], char buffer[], int flags, char flag_ch, int width, int precision, int size)
{
    unsigned long int num = va_arg(types, unsigned long int);
    num = convert_size_unsgnd(num, size);
    return write_unsgnd(16, num, buffer, flags, width, precision, size, map_to, flag_ch);
}

