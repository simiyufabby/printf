#include "main.h"
#include <stdlib.h>
/**
 * print_string - Prints a string with special formatting for non-printablechar
 *
 * @args: A va_list containing the string to be printed.
 *
 * Return: The number of characters printed (excluding the null byte).
 */
void print_string(va_list args)
{
	char *str = va_arg(args, char *);
	char *hex_repr;
	int i;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return;
	}

	for (i = 0; str[i]; i++)
	{
	if (str[i] < 32 || str[i] >= 127)
	{
	hex_repr = convert_to_hex(str[i]);
	write(1, "\\x", 2);
	write(1, hex_repr, 2);
	free(hex_repr);
	}
	else if (str[i] == '\n')
	{
	write(1, "\\x0A", 4);
	}
	else
	{
	write(1, &str[i], 1);
	}
	}
}
