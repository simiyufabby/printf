#include "main.h"

/**
 * _printf - function prints output according to format.
 * @format: character string containing zero or more directives.
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;
	const char *str;
	const char *non_printable_str;
	int plus_flag, space_flag, hash_flag;
	int length_modifier = 0;
	int field_width = 0;
	int precision = -1;
	int zero_flag;
	int left_justify_flag;
	(void)left_justify_flag;
	(void)plus_flag;
	(void)space_flag;
	(void)hash_flag;
	(void)zero_flag;
	(void)length_modifier;

	va_start(args, format);
	
	while (*format)
	{
		if (*format == '%')
		{
			format++;

			if (*format == '\0')
				break;
			plus_flag = 0;
			space_flag = 0;
			hash_flag = 0;
			zero_flag = 0;
			left_justify_flag = 0;

			while (*format == '+' || *format == ' ' || *format == '#')
			{
				if (*format == '+')
					plus_flag = 1;
				else if (*format == ' ')
					space_flag = 1;
				else if (*format == '#')
					hash_flag = 1;
				else if (*format == '0')
					zero_flag = 1;
				else if (*format == '-')
					left_justify_flag = 1;
				format++;
			}

			if (*format == 'l')
			{
				length_modifier = 1;
				format++;
			}

			else if (*format == 'h')
			{
				length_modifier = -1;
				format++;
			}

			while (*format >= '0' && *format <= '9')
			{
				field_width = field_width * 10 + (*format - '0');
				format++;
			}

			if (*format == '.')
			{
				format++;
				precision = 0;
				while (*format >= '0' && *format <= '9')
				{
					precision = precision * 10 + (*format - '0');
					format++;
				}
			}
			
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

			case 'r':
				{
					char *str = va_arg(args, char *);
					reverse_string(str);
					while (*str)
					{
						putchar(*str);
						str++;
						printed_chars++;
					}
				}
				break;

			case 'R':
				{
					char *str = va_arg(args, char *);
					rot13(str);
					while (*str)
					{
						putchar(*str);
						str++;
						printed_chars++;
					}
				}
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
 * _print_binary - Function Prints an unsigned integer in binary format.
 *
 * @num: unsigned integer to be printed in binary format.
 *
 * Return: The number of characters printed
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
 * print_number - Prints an integer to  standard output.
 * @n: integer to be printed.
 * Return: The number of characters printed
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
 * print_unsigned - Prints an unsigned integer to standard output.
 * @n: unsigned integer to be printed.
 * Return: number of characters printed
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
 * print_octal - Prints an unsigned int in octal format to standard output.
 * @n: unsigned integer to be printed.
 * Return: The number of characters printed
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
 * print_hex - Prints an unsigned int in hexadecimal format to standard output.
 * @n: unsigned integer to be printed.
 * @uppercase: print in uppercase (1) or lowercase (0) hexadecimal format.
 * Return: number of characters printed
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
 * print_non_printable - Prints non-printable character in specified format.
 * @c: character to be printed.
 * Return: The number of characters printed
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

/**
 * reverse_string - Reverses a given string in-place.
 * @str: The string to be reversed.
 *
 * Return: void
 */
void reverse_string(char *str)
{
	int len;
	char temp;
	int i;

	if (str == NULL)
		return;

	len = 0;

	while (str[len] != '\0')
		len++;

	for (i = 0; i < len / 2; i++)
	{
		temp = str[i];

		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
}

/**
 * rot13 - Applies the ROT13 cipher to a string.
 * @str: The string to be encoded.
 *
 * Return: void
 */
void rot13(char *str)
{
	int i;
	char c;
	char base;

	if (str == NULL)
		return;

	for (i = 0; str[i] != '\0'; i++)
	{
		c = str[i];

		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		{
			base = (c >= 'A' && c <= 'Z') ? 'A' : 'a';
			str[i] = (c - base + 13) % 26 + base;
		}
	}
}
