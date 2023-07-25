#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>

int _printf(const char *format, ...);
int _print_binary(unsigned int num);
int print_number(int n);
int print_unsigned(unsigned int n);
int print_octal(unsigned int n);
int print_hex(unsigned int n, int uppercase);
void reverse_string(char *str);
int print_non_printable(char c);
int print_address(void *ptr);
void rot13(char *str);

#endif
