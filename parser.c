
#include "parser.h"
#include "printer.h"

/**
 * __case_default - Handles the default case.
 * @format: Template string.
 * @current: The current index we are in the template string.
 * @printed: A reference to an integer that's counting the number of
 * printed characters.
 * Return: Nothing.
 */
static void __case_default(const char *format, int current, int *printed)
{
	if (!__write_char('%', printed))
	{
		exit(-1);
	}

	if (!__write_char(format[current], printed))
	{
		exit(-1);
	}
}

/**
 * __case_percent - Handles the case where the format is to print a percentage
 * sign.
 * @printed: A reference to an integer that's counting the number of printed
 * characters.
 * Return: Nothing.
 */
static void __case_percent(int *printed)
{
	if (!__write_char('%', printed)) /* If this failed. */
	{
		/* Tell the user we failed to write some characters. */
		exit(-1);
	}
}

/**
 * __case_number - Handles the case where t print a number.
 * @args: The variadic list to eat the number from.
 * @printed: A reference to an integer that's counting the number
 * of printed characters.
 * Return: Nothing.
*/
static void __case_number(va_list args, int *printed)
{
	if (!__write_number(args, printed))
	{
		/* Tell the user we failed to write. */
		exit(-1);
	}
}

/**
 * __case_number - Handles the case where t print a number.
 * @args: The variadic list to eat the number from.
 * @printed: A reference to an integer that's counting the number
 * of printed characters.
 * Return: Nothing.
*/
static void __case_unsigned(va_list args, int *printed)
{
	if (!__write_unsigned(args, printed))
	{
		/* Tell the user we failed to write. */
		exit(-1);
	}
}

/**
 * __printf_parseString -  Utility function that parses the template info
 * inside of string @format. Useful because of tidiness. Really.
 *
 * @format: The string to use as a template when printing to stdout.
 * @args: The of arguments bound to the print.
 * Return: the length of characters we printed after formatting.
 */
int __printf_parseString(const char *format, va_list args)
{
	int printed, current;

	printed = 0;

	for (current = 0; format[current] != '\0'; current++)
	{
		if (format[current] == '%')
		{
			current++; /* Move away from the percentage sign into the f_type */

			switch (format[current])
			{
				case '%': /* have we found a format specifier? */ {
					__case_percent(&printed);
				}	break;

				case 'i':
				case 'd': {
					__case_number(args, &printed);
				}	break;

				case 'u': {
					__case_unsigned(args, &printed);
				}	break;

				default: { /* If it is unknown, just print as is. */
					__case_default(format, current, &printed);
				}	break;
			}
		}

		else
		{
			/* Since this is just a regular character, we write as is. */
			__write_char(format[current], &printed);
		}
	}
	return (printed);
}
