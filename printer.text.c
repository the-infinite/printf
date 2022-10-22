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

	str = (char *) va_arg(args, void *);

	for (i = 0; str[i] != 0; i++)
	{
		if (!__write_char(str[i], printed))
			return (0);
	}

	return (1);
}

/**
 * __write_buffer - Print all chars in a buffer to the standard output stream
 * and increment the value stored in printed if we succeed.
 *
 * @buffer: The character pointer to print.
 * @printed: A pointer to some integer indicating the number of characters we
 * have printed.
 *
 * Return: The number of characters printed and 0 if we failed to print.
 */
int __write_buffer(char *buffer, int *printed)
{
	int result;

	result = (write(1, buffer, 1024));

	if (result > 0)
	{
		/*
		*Increment the number of printed characters, I am adding this here
		* to make it more difficult to forget to do so.
		*/
		++(*printed);
	}

	return ((result > 0) ? result : 0);
}

