#include "main.h"
#include <stdlib.h>
/**
 * convert_to_hex - Converts a character's ASCII code to hexadecimal.
 *
 * @ch: The character to convert.
 *
 * Return: The hexadecimal representation of the character
 */
char *convert_to_hex(char ch)
{
	char *hex_repr = malloc(3);

	if (hex_repr == NULL)
	{
	fprintf(stderr, "Memory allocation failed\n");
	exit(EXIT_FAILURE);
	}

	if (ch == '\n')
	{
	sprintf(hex_repr, "\\x0A");
	}
	else
	{
	sprintf(hex_repr, "\\x%02X", (unsigned char)ch);
	}
	return (hex_repr);
}
