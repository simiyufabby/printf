#include "main.h"

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
