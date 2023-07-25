#include "main.h"

/**
 * print_non_printable - Prints a non-printable character in the specified format.
 * @c: The character to be printed.
 * Return: The number of characters printed (excluding the null byte).
 */

int print_non_printable(char c)
{
	if (c < 32 || c >= 127)
	{
		return printf("\\x%02X", (unsigned char)c);
	}
	else
	{
		putchar(c);
		return (1);
	}
}
