#include "main.h"

/**
 * is_printable - Check if a character is printable
 * @c: The character to be checked
 *
 * Returns: 1 if c is printable, 0 otherwise
 */
int is_printable(char c)
{
    return (c >= 32 && c < 127);
}

/**
 * append_hexa_code - Append ASCII in hexadecimal code to buffer
 * @buffer: The character array
 * @index: The index to start appending
 * @ascii_code: ASCII code
 *
 * Returns: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int index)
{
    char map_to[] = "0123456789ABCDEF";
    /* Hexadecimal format code is always 2 digits long */
    if (ascii_code < 0)
        ascii_code *= -1;

    buffer[index++] = '\\';
    buffer[index++] = 'x';
    buffer[index++] = map_to[ascii_code / 16];
    buffer[index] = map_to[ascii_code % 16];

    return 3;
}

/**
 * is_digit - Check if a character is a digit
 * @c: The character to be checked
 *
 * Returns: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

/**
 * convert_size_number - Cast a number to the specified size
 * @num: The number to be casted
 * @size: The size indicating the type to be casted
 *
 * Returns: Casted value of num
 */
long int convert_size_number(long int num, int size)
{
    if (size == S_LONG)
        return num;
    else if (size == S_SHORT)
        return (short)num;

    return (int)num;
}

/**
 * convert_size_unsgnd - Cast a number to the specified size
 * @num: The number to be casted
 * @size: The size indicating the type to be casted
 *
 * Returns: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
    if (size == S_LONG)
        return num;
    else if (size == S_SHORT)
        return (unsigned short)num;

    return (unsigned int)num;
}

