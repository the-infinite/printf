#include <stdlib.h>

#include "printer.h"

/**
* __write_character - Write a character to stdout.
* @args: The variadic argument list we take this character from.
* @printed: A reference to the number of characters printed so far.
* Return: 0 if we failed to print and the 1 otherwise.
*/
int __write_character(va_list args, int *printed)
{
	char value;

	value = (char) va_arg(args, int);

	return (__write_char(value, printed));
}

/**
* __write_string - Write a string to stdout.g
* @args: The variadic argument list we take this string from.
* @printed: A reference to the number of characters printed so far.
* Return: 0 if we failed to print and 1 otherwise.
*/
int __write_string(va_list args, int *printed)
{
	int i;
	char *str;

	str = va_arg(args, char *);

	for (i = 0; str[i] != 0; i++)
	{
		if (!__write_char(str[i], printed))
			return (0);
	}

	return (1);
}
