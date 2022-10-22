#include <stdlib.h>
#include <stdio.h>

#include "printer.h"
#include "main.h"


/**
* __util_reverse - A utility function to reverse a string.
* @str: The string to reverse.
* @size: The size of the string to reverse.
* Return: @str reversed and NULL if str is an empty or NULL string.
*/
char *__util_reverse(char *str, size_t size)
{
	char *reversed;

	unsigned int i, end;

	if (str == NULL || size == 0)
	{
		return (NULL);
	}

	/* Pad with an extra slot for the NULL terminator. */
	reversed = malloc(sizeof(char) * (size + 1));
	end = size % 2 == 0 ? size / 2 : (size + 1)/2;

	for (i = 0; i < end; i++)
	{
		if(str[i] && str[size - i - 1])
		{
			char tmp = str[i];

			reversed[i] = str[size - i - 1];
			reversed[size - i - 1] = tmp;
		}
	}

	reversed[size] = 0;

	return (reversed);
}

/**
* __write_hex - This is a function that prints a hexadecimal number to the
* format specified.
* @args: The variable arguments list we expect this number to come from.
* @printed: A pointer to the number of characters we have printed so far
* @upper: Should this be printed in uppercase?
* Return: True if printed and false otherwise.
*/
int __write_hex(va_list args, int *printed, char upper)
{
	long int value, pos = 0, i;
	char *digits;
	char *ret, *final;

	if (upper)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";

	value = va_arg(args, long int);
	ret = malloc(sizeof(char) * 64);

	while (value > 0)
	{
		unsigned int digit;

		digit = value % 16; /* What is the remainder when we divide by 16? */
		ret[pos++] = digits[digit]; /* Look for the digit in B-16 encode*/

		/*Divide the current value of value by 16 to shift to the next digit*/
		value /= 16;
	}

	ret[pos] = 0; /* Append a null character to the tail of the string. */
	final = __util_reverse(ret, (size_t)pos);

	/* Deallocate this piece of memory since it is now unused */
	free(ret);

	for (i = 0; i < pos; i++)
	{
		if(!__write_char(final[i], printed)) {
			return (0);
		}
	}

	return (1);
}

/**
* __write_pointer - This is a function that prints a hexadecimal number to the
* format specified.
* @args: The variable arguments list we expect this pointer to come from.
* @printed: A pointer to the number of characters we have printed so far
* @upper: Should this be printed in uppercase?
* Return: True if printed and false otherwise.
*/
int __write_pointer(va_list args, int *printed, char upper)
{
	unsigned long int value, pos = 0, i;
	char *digits;
	char *ret, *final;

	if (upper)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";

	value = (unsigned long int) va_arg(args, void*);
	ret = malloc(sizeof(char) * 32);

	while (value > 0)
	{
		unsigned int digit;

		digit = value % 16; /* What is the remainder when we divide by 16? */
		ret[pos++] = digits[digit]; /* Look for the digit in B-16 encode*/

		/*Divide the current value of value by 16 to shift to the next digit*/
		value /= 16;
	}

	ret[pos] = 0; /* Append a null character to the tail of the string */
	final = __util_reverse(ret, (size_t)pos);

	free(ret);

	if (!__write_char('0', printed))
		return (0);

	if (!__write_char('x', printed))
		return (0);

	for (i = 0; i < pos; i++)
		if (!__write_char(final[i], printed))
			return (0);

	return (1);
}


