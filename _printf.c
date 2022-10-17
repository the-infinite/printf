#include "main.h"

/**
 * _printf - Prints a varying list of arguments of any type using the
 * template specified.
 * @format: The template string to use.
 * Return: The number of characters printed by this function or -1 if we fail
 * to print.
 */
int _printf(const char *format, ...)
{
	/* Where we keep the number of printed characters. */
	int printed;

	/* This is the list of all arguments. */
	va_list args;


	/*If you did not add a key note, string, we just tell you nonsense too.*/
	if (format == NULL)
	{
		/*
		* Just return -1 in this case.
		* TODO: #1 Append this return value to the man file.
		*/
		return (-1);
	}

	/* Indicate the boundary where this variadic argument starts */
	va_start(args, format);
	printed = __printf_parseString(format, args);

	/* Mark the end of this variadic argument. */
	va_end(args);

	/* In the end, just return the number of characters you printed. */
	return (printed);
}
