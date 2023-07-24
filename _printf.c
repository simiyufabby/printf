#include "main.h"

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
 * _printf - Prints output according to a format.
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
