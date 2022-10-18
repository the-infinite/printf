#include "printer.h"

#include <stdlib.h>

/**
 * __write_char - Print a single character to the standard output stream and
 * increment the value stored in printed if we succeed.
 *
 * @c: The character to print.
 * @printed: A pointer to some integer indicating the number of characters we
 * have printed.
 *
 * Return: The number of characters printed and -1 if we failed to print.
 */
int __write_char(char c, int *printed)
{
	int result;

	result = (write(1, &c, 1));

	if (result > 0)
	{
		/*
		*Increment the number of printed characters, I am adding this here
		* to make it more difficult to forget to do so.
		*/
		++(*printed);
	}

	return (result > 0);
}

/**
* raise - Raises 10 by a set value.
*
* @n: Raise 10 to the power of n
* Return: 10 raised to @n
*/
static int raise(int n)
{
	int ret = 1;

	int i = n;

	while (i > 0)
	{
		ret = ret * 10;
		i--;
	}

	return (ret);
}

/**
* __write_number - Prints the string value of a number to the standard
* output stream.
* @args: The variadic argument list we take this number from.
* @printed: A reference to the printed number.
* Return: 0 if we failed to print and the length of characters printed
* otherwise.
*/
int __write_number(va_list args, int *printed)
{
	int value, temp, digits;


	value = va_arg(args, int);
	digits = 0;

	if (value < 0) /* If this number is negative */
	{
		if (!__write_char(45, printed))
			return (0); /* Start with the minus sign */
		value = value * -1; /* Absolute value only */
	}

	temp = value; /*Used to calculate the number of digits temporarily */

	while (1) /* Count the number of digits in this number */
	{
		temp /= 10;
		digits++;
		if (temp < 1)
			break;
	}

	while (digits > 0)
	{
		char c;

		/* The current character representing a digit of this number. */
		c = (value / raise(--digits) % 10) + 48;

		/* Write that single digit to the output stream. */
		if (!__write_char(c, printed))
			return (0);
		if (digits < 1)
			break;
	}

	/* Since we made it this far, it is safe to say it worked. */
	return (1);
}

/**
* __write_ui - Prints the string value of a number to the standard
* output stream as an unsigned number.
* @args: The variadic argument list we take this number from.
* @printed: A reference to the printed number.
* Return: 0 if we failed to print and the length of characters printed
* otherwise.
*/
int __write_ui(va_list args, int *printed)
{
	unsigned int value, temp, digits;

	value = va_arg(args, unsigned int);
	digits = 0;
	temp = value; /*Used to calculate the number of digits temporarily */

	while (1) /* Count the number of digits in this number */
	{
		temp /= 10;
		digits++;
		if (temp < 1)
			break;
	}

	while (digits > 0)
	{
		char c;

		/* The current character representing a digit of this number. */
		c = (value / raise(--digits) % 10) + 48;

		/* Write that single digit to the output stream. */
		if (!__write_char(c, printed))
			return (0);
		if (digits < 1)
			break;
	}

	/* Since we made it this far, it is safe to say it worked. */
	return (1);
}
