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
 * __case_number - Handles the case where to print a number.
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
 * __case_ui - Handles the case where to print an unsigned number.
 * @args: The variadic list to eat the number from.
 * @printed: A reference to an integer that's counting the number
 * of printed characters.
 * Return: Nothing.
*/
static void __case_ui(va_list args, int *printed)
{
	if (!__write_ui(args, printed))
	{
		/* Tell the user we failed to write. */
		exit(-1);
	}
}

/**
 * __case_hex - Handles the case where to print a hexadecimal number.
 * @args: The variadic list to eat the number from.
 * @printed: A reference to an integer that's counting the number
 * @upper: Are we doing this in uppercase?
 * of printed characters.
 * Return: Nothing.
*/
static void __case_hex(va_list args, int *printed, char upper)
{
	if (!__write_hex(args, printed, upper))
	{
		exit(-1);
	}
}

/**
 * __do_switch - Performs the necessary case control for the parsing of format
 * specifiers.
 * @format: The template string.
 * @current: A pointer to the current integer.
 * @printed: The number of characters we have printed so far.
 * @args: The list of variable arguments.
 * Return: Nothing.
*/
static void __do_switch(const char *format, int *current, int *printed,
va_list args) {
	switch (format[*current])
	{
		case '%': /* have we found a percent literal? */ {
			__case_percent(printed);
		}	break;

		case 'X': case 'x': {
			__case_hex(args, printed, format[*current] == 'X');
		}	break;

		case 'P': case 'p': {
			if (!__write_pointer(args, printed, format[*current] == 'P'))
			{
				exit(-1);
			}
		}	break;

		case 'i': case 'd': {
			__case_number(args, printed);
		}	break;

		case 'u': {
			__case_ui(args, printed);
		}	break;

		default: { /* If it is unknown, just print as is. */
			__case_default(format, *current, printed);
		}	break;
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
			__do_switch(format, &current, &printed, args);
		}

		else
		{
			/* Since this is just a regular character, we write as is. */
			__write_char(format[current], &printed);
		}
	}
	return (printed);
}
