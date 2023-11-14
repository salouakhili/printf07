#include "main.h"

/* Function declarations */
int print_char(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_int(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Array of function pointers */
fmt_t print_functions[] = {
	{'c', print_char},
	{'s', print_string},
	{'%', print_percent},
	{'d', print_int},
	{'i', print_int},
	{'b', print_binary},
	{0, NULL} /* Null terminator for the array */
};

/**
 * print_char - Prints a char
 */
int print_char(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);
	return handle_write_char(c, buffer, flags, width, precision, size);
}

/**
 * print_string - Prints a string
 */
int print_string(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	char *str = va_arg(types, char *);
	int length = (str == NULL) ? 6 : 0;

	while (str && str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	return handle_write_string(str, buffer, flags, width, length);
}

/**
 * print_percent - Prints a percent sign
 */
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	UNUSED(types);
	return handle_write_char('%', buffer, flags, width, precision, size);
}

/**
 * print_int - Print int
 */
int print_int(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	long int n = va_arg(types, long int);
	n = convert_size_number(n, size);

	return handle_write_number(n, buffer, flags, width, precision);
}

/**
 * print_binary - Prints an unsigned number in binary
 */
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	unsigned int n = va_arg(types, unsigned int);
	return handle_write_binary(n, buffer, flags, width, precision);
}

