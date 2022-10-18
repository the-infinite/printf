#include <stdlib.h>
#include <stdio.h>

#include "printer.h"

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
 * __octal_print - Print an octal number.
 *
 * @value: The number to print.
 * @printed: The pointer to the count of all characters printed so far.
 * Return: True if Printed and False otherwise
 */
static int __octal_print(long int value, int *printed)
{
	long int digits, temp;

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

/**
* __write_octal - This is a function that prints a number in base 8 to the
* format specified.
* @args: The variable arguments list we expect this number to come from.
* @printed: A pointer to the number of characters we have printed so far
* Return: True if printed and false otherwise.
*/
int __write_octal(va_list args, int *printed)
{
	long int octalNum = 0, placeValue = 1;
	unsigned int dNo = va_arg(args, unsigned int);

	while (dNo > 0)
	{
		octalNum += (dNo % 8) * placeValue;
		dNo /= 8;
		placeValue *= 10;
	}

	return (__octal_print(octalNum, printed));
}
