#include "main.h"
#include <stdarg.h>

/**
 * _printf - function prints output according to a format.
 *
 * @format: A character string containing zero or more directives.
 *
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;
	const char *str;
	const char *non_printable_str;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;

			if (*format == '\0')
				break;

			switch (*format)
			{
			case 'c':
				putchar(va_arg(args, int));
				printed_chars++;
				break;

			case 's':
				str = va_arg(args, const char *);

				while (*str)
				{
					putchar(*str);
					str++;
					printed_chars++;
				}
				break;

			case 'd':
			case 'i':
				{
					int num = va_arg(args, int);
					int divisor = 1;

					if (num < 0)
					{
						putchar('-');
						printed_chars++;
						num = -num;
					}

					while (num / divisor > 9)
						divisor *= 10;

					while (divisor)
					{
						putchar('0' + num / divisor);
						printed_chars++;
						num %= divisor;
						divisor /= 10;
					}
				}
				break;

			case 'b':
				printed_chars += _print_binary(va_arg(args, unsigned int));
				break;


			case '%':
				putchar('%');
				printed_chars++;
				break;

			case 'u':
				printed_chars += print_unsigned(va_arg(args, unsigned int));
				break;

			case 'o':
				printed_chars += print_octal(va_arg(args, unsigned int));
				break;
			case 'x':
				printed_chars += print_hex(va_arg(args, unsigned int), 0);
				break;

			case 'X':
				printed_chars += print_hex(va_arg(args, unsigned int), (*format == 'X'));
				break;

			case 'S':
				non_printable_str = va_arg(args, const char *);
				while (*non_printable_str)
				{
					printed_chars += print_non_printable(*non_printable_str);
					non_printable_str++;
				}
				break;
			case 'p':
				printed_chars += print_address(va_arg(args, void *));
				break;

			default:
				putchar('%');
				putchar(*format);
				printed_chars += 2;
				break;
			}
		}
		else
		{
			putchar(*format);
			printed_chars++;
		}
	format++;
	}
	va_end(args);
	return (printed_chars);
}

/**
 * _print_binary - Prints an unsigned integer in binary format.
 *
 * @num: The unsigned integer to be printed in binary format.
 *
 * Return: The number of characters printed (excluding the null byte).
 */
int _print_binary(unsigned int num)
{
	int printed_chars = 0;
	int binary[32];
	int j;
	int i;

	if (num == 0)
	{
		putchar('0');
		return (1);
	}
	for (i = 0; num > 0; i++)
	{
		binary[i] = num % 2;
		num /= 2;
	}
	for (j = i - 1; j >= 0; j--)
	{
	putchar('0' + binary[j]);
	printed_chars++;
	}

	return (printed_chars);
}
/**
 * print_number - Prints an integer to the standard output.
 * @n: The integer to be printed.
 * Return: The number of characters printed (excluding the null byte).
 */
int print_number(int n)
{
	if (n < 0)
	{
		putchar('-');
		n = -n;
	}

	return print_unsigned(n);

}

/**
 * print_unsigned - Prints an unsigned integer to the standard output.
 * @n: The unsigned integer to be printed.
 * Return: The number of characters printed (excluding the null byte).
 */
int print_unsigned(unsigned int n)
{
	char unsigned_buffer[100];
	int i = 0;
	int printed_chars = 0;

	if (n == 0)
	{
		putchar('0');
		return (1);
	}

	while (n != 0)
	{
		unsigned_buffer[i] = '0' + (n % 10);
		n /= 10;
		i++;
	}

	for (i = i - 1; i >= 0; i--)
	{
		putchar(unsigned_buffer[i]);
		printed_chars++;
	}

	return (printed_chars);
}

/**
 * print_octal - Prints an unsigned integer in octal format to the standard output.
 * @n: The unsigned integer to be printed.
 * Return: The number of characters printed (excluding the null byte).
 */
int print_octal(unsigned int n)
{
	int octal_digits[100];
	int i = 0;
	int printed_chars = 0;

	if (n == 0)
	{
		putchar('0');
		return (1);
	}

	while (n != 0)
	{
		octal_digits[i] = n % 8;
		n /= 8;
		i++;
	}
	for (i = i - 1; i >= 0; i--)
	{
		putchar('0' + octal_digits[i]);
		printed_chars++;
	}

	return (printed_chars);
}

/**
 * print_hex - Prints an unsigned integer in hexadecimal format to the standard output.
 * @n: The unsigned integer to be printed.
 * @uppercase: Whether to print in uppercase (1) or lowercase (0) hexadecimal format.
 * Return: The number of characters printed (excluding the null byte).
 */
int print_hex(unsigned int n, int uppercase)
{
	const char *hex_digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
	int printed_chars = 0;
	char hex_buffer[32];
	int i = 0;

	if (n == 0)
	{
		putchar('0');
		return (1);
	}

	while (n != 0)
	{
		hex_buffer[i] = hex_digits[n % 16];
		n /= 16;
		i++;
	}

	for (i = i - 1; i >= 0; i--)
	{
		putchar(hex_buffer[i]);
		printed_chars++;
	}

	return (printed_chars);
}

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

/**
 * print_address - Prints a pointer's address in hexadecimal format.
 * @ptr: The pointer to be printed.
 * Return: The number of characters printed (excluding the null byte).
 */
int print_address(void *ptr)
{
	uintptr_t address = (uintptr_t)ptr;
	char buffer[18];

	snprintf(buffer, sizeof(buffer), "0x%lx", address);

	return printf("%s", buffer);
}
