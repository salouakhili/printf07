#include "main.h"

/**
 * print_char - Prints a character
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	char c = va_arg(args, int);
	return handle_write_char(c, buffer, flags, width, precision, size);
}

/**
 * print_string - Prints a string
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	char *str = va_arg(args, char *);
	int length = (str == NULL) ? 6 : str_len(str);
	int printed = 0;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			printed += write_str(buffer, str, length);
			printed += write_padding(' ', width - length);
		}
		else
		{
			printed += write_padding(' ', width - length);
			printed += write_str(buffer, str, length);
		}
	}
	else
	{
		printed += write_str(buffer, str, length);
	}

	return printed;
}

/**
 * print_percent - Prints a percent sign
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	UNUSED(args);
	UNUSED(precision);
	UNUSED(size);
	if (width > 1)
	{
		if (flags & F_MINUS)
		{
			write_str(buffer, "%", 1);
			write_padding(' ', width - 1);
		}
		else
		{
			write_padding((flags & F_ZERO) ? '0' : ' ', width - 1);
			write_str(buffer, "%", 1);
		}
		return width;
	}
	else
	{
		return write_str(buffer, "%", 1);
	}
}

/**
 * print_int - Prints an integer
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_int(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	long int n = convert_size_number(va_arg(args, long int), size);
	int is_negative = (n < 0);
	int printed = 0;

	if (n == 0)
		printed += write_num(buffer, '0', flags, width, precision, 1, ' ', 0);
	else
		printed += write_number(is_negative, '0', buffer, flags, width, precision, size);

	return printed;
}

/**
 * print_binary - Prints a binary number
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_binary(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	unsigned int n = va_arg(args, unsigned int);
	char *binary_str = convert_to_binary(n);
	int length = str_len(binary_str);
	int printed = 0;

	if (precision > 0 && precision > length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			printed += write_str(buffer, binary_str, length);
			printed += write_padding(' ', width - length);
		}
		else
		{
			printed += write_padding(' ', width - length);
			printed += write_str(buffer, binary_str, length);
		}
	}
	else
	{
		printed += write_str(buffer, binary_str, length);
	}

	free(binary_str);
	return printed;
}

