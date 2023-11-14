#include "main.h"

/**
 * print_unsigned - Prints an unsigned number
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_unsigned(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	unsigned long int num = convert_size_unsgnd(va_arg(args, unsigned long int), size);
	return write_unsgnd(0, '0', buffer, flags, width, precision, num);
}

/**
 * print_octal - Prints an unsigned number in octal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_octal(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	unsigned long int num = convert_size_unsgnd(va_arg(args, unsigned long int), size);
	return write_unsgnd(0, '0', buffer, flags, width, precision, num);
}

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	return print_hexa(args, "0123456789abcdef", buffer, flags, 'x', width, precision, size);
}

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexa_upper(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	return print_hexa(args, "0123456789ABCDEF", buffer, flags, 'X', width, precision, size);
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper case
 * @args: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @flag_ch: Active flag character
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexa(va_list args, char map_to[], char buffer[], int flags, char flag_ch, int width, int precision, int size)
{
	unsigned long int num = convert_size_unsgnd(va_arg(args, unsigned long int), size);
	return write_unsgnd(flag_ch, '0', buffer, flags, width, precision, num, map_to, 16);
}

