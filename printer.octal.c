#include <stdlib.h>
#include <stdio.h>

#include "printer.h"
#include "main.h"


/**
* __write_octal - This is a function that prints a number in base 8 to the
* format specified.
* @args: The variable arguments list we expect this number to come from.
* @printed: A pointer to the number of characters we have printed so far
* Return: True if printed and false otherwise.
*/
int __write_octal(va_list args, int *printed)
{
	long int value, pos = 0, i;
	const char *digits = "01234567";
	char *ret, *final;

	value = va_arg(args, long int);
	ret = malloc(sizeof(char) * 64);

	while (value > 0)
	{
		unsigned int digit;

		digit = value % 8; /* What is the remainder when we divide by 16? */
		ret[pos++] = digits[digit]; /* Look for the digit in B-16 encode*/

		/*Divide the current value of value by 16 to shift to the next digit*/
		value /= 8;
	}

	ret[pos] = 0; /* Append a null character to the tail of the string. */
	final = __util_reverse(ret, (size_t)pos);

	/* Deallocate this piece of memory since it is now unused */
	free(ret);

	for (i = 0; i < pos; i++)
	{
		if (!__write_char(final[i], printed))
			return (0);
	}

	return (1);
}
