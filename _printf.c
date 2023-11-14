#include "main.h"

/**
 * _printf - Printf function
 * @format: Format string.
 * Return: Number of printed characters.
 */
int _printf(const char *format, ...)
{
	int printed_chars = 0;
	va_list args;
	char buffer[BUFF_SIZE];
	int buff_ind = 0;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
		{
			buffer[buff_ind++] = *format;
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			printed_chars += handle_format(&format, args, buffer, &buff_ind);
		}

		format++;
	}

	print_buffer(buffer, &buff_ind);
	va_end(args);

	return (printed_chars);
}

/**
 * handle_format - Handles the format specifier and prints the argument
 * @format: Pointer to the format string.
 * @args: Variable arguments list.
 * @buffer: Array of chars to handle print.
 * @buff_ind: Index at which to add the next char, represents the length.
 *
 * Return: Number of printed characters.
 */
int handle_format(const char **format, va_list args, char buffer[], int *buff_ind)
{
	int printed = 0;
	int flags, width, precision, size;

	(*format)++; /* Move past the '%' character */
	flags = get_flags(*format, format);
	width = get_width(*format, format, args);
	precision = get_precision(*format, format, args);
	size = get_size(*format, format);

	printed = handle_print(*format, format, args, buffer,
		flags, width, precision, size);

	if (printed == -1)
		return (-1);

	*buff_ind += printed;

	return (printed);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars.
 * @buff_ind: Index at which to add the next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, buffer, *buff_ind);

	*buff_ind = 0;
}

