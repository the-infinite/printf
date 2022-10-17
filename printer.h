#ifndef Alx_PrintF_PrintUtilities_H
#define Alx_PrintF_PrintUtilities_H

#include <unistd.h>
#include <stdarg.h>

int __write_char(char c, int *printed);
int __write_number(va_list args, int *printed);
int __write_ui(va_list args, int *printed);

#endif /* Alx_PrintF_PrintUtilities_H */