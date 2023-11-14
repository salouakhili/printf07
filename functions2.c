#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	void *address = va_arg(args, void *);
	char map_to[] = "0123456789abcdef";
	int length, padd_start;
	char extra_char, padd_char;

	if (address == NULL)
		return (write(1, "(nil)", 5));

	length = handle_pointer_length(address, map_to);
	padd_char = (flags & F_ZERO) && !(flags & F_MINUS) ? '0' : ' ';
	extra_char = handle_pointer_extra_char(flags);
	padd_start = handle_pointer_padding_start(flags);

	return (write_pointer(buffer, length, width, flags, padd_char, extra_char, padd_start, map_to));
}

/**
 * handle_pointer_length - Calculate the length of a pointer value
 * @address: Pointer variable
 * @map_to: Mapping for hexadecimal conversion
 * Return: Length of the pointer value
 */
int handle_pointer_length(void *address, char map_to[])
{
	int length = 2; /* for '0x' */
	unsigned long int num_address = (unsigned long)address;

	while (num_address > 0)
	{
		num_address /= 16;
		length++;
	}

	return length;
}

/**
 * handle_pointer_extra_char - Calculate the extra character for a pointer
 * @flags: Active flags
 * Return: Extra character for the pointer
 */
char handle_pointer_extra_char(int flags)
{
	char extra_char = 0;

	if (flags & F_PLUS)
		extra_char = '+';

	return extra_char;
}

/**
 * handle_pointer_padding_start - Calculate the index where padding should start
 * @flags: Active flags
 * Return: Index where padding should start
 */
int handle_pointer_padding_start(int flags)
{
	int padd_start = 1;

	if (flags & F_PLUS || flags & F_SPACE)
		padd_start++;

	return padd_start;
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd_char: Char representing the padding
 * @extra_char: Char representing extra char
 * @padd_start: Index at which padding should start
 * @map_to: Mapping for hexadecimal conversion
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int length, int width, int flags, char padd_char, char extra_char, int padd_start, char map_to[])
{
	int i;

	if (width > length)
	{
		for (i = padd_start; i < width - length + padd_start; i++)
			buffer[i] = padd_char;

		buffer[i] = '\0';

		if (flags & F_MINUS)
			return (write(1, "0x", 2) + write(1, &buffer[padd_start], length - padd_start) + write(1, &buffer[i], width - length - padd_start));
		else
			return (write(1, &buffer[padd_start], width - length) + write(1, "0x", 2) + write(1, &buffer[i], length - padd_start));
	}

	buffer[padd_start] = '\0';

	if (extra_char)
		buffer[--padd_start] = extra_char;

	return (write(1, "0x", 2) + write(1, &buffer[padd_start], length - padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ASCII codes in hexa of non-printable chars
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	char *str = va_arg(args, char *);

	if (str == NULL)
		return (write(1, "(null)", 6));

	return handle_non_printable(buffer, str);
}

/**
 * handle_non_printable - Handle the non-printable characters
 * @buffer: Buffer array to handle print
 * @str: Input string
 * Return: Number of chars printed
 */
int handle_non_printable(char buffer[], char *str)
{
	int i = 0, offset = 0, count = 0;

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return write(1, buffer, i + offset);
}

/**
 * is_printable - Check if a character is printable
 * @c: Character to check
 * Return: 1 if printable, 0 otherwise
 */
int is_printable(char c)
{
	return c >= 32 && c <= 126;
}

/**
 * append_hexa_code - Append hexadecimal code for a non-printable character
 * @c: Non-printable character
 * @buffer: Buffer array to handle print
 * @index: Index at which to append the code
 * Return: Length of the appended code
 */
int append_hexa_code(char c, char buffer[], int index)
{
	buffer[index++] = '\\';
	buffer[index++] = 'x';
	buffer[index++] = (c / 16) < 10 ? (c / 16) + '0' : (c / 16) - 10 + 'a';
	buffer[index++] = (c % 16) < 10 ? (c % 16) + '0' : (c % 16) - 10 + 'a';

	return 3;
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_reverse(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	char *str = va_arg(args, char *);

	if (str == NULL)
		str = ")Null(";

	return handle_reverse(buffer, str);
}

/**
 * handle_reverse - Handle the reverse string
 * @buffer: Buffer array to handle print
 * @str: Input string
 * Return: Number of chars printed
 */
int handle_reverse(char buffer[], char *str)
{
	int i, count = 0;

	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		write(1, &str[i], 1);
		count++;
	}

	return count;
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list args, char buffer[], int flags, int width, int precision, int size)
{
	char *str = va_arg(args, char *);

	if (str == NULL)
		str = "(AHYY)";

	return handle_rot13(buffer, str);
}

/**
 * handle_rot13 - Handle the rot13 transformation
 * @buffer: Buffer array to handle print
 * @str: Input string
 * Return: Number of chars printed
 */
int handle_rot13(char buffer[], char *str)
{
	char x;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}

	return count;
}

