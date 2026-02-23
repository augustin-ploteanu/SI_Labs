#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>

void trim_inplace(char *s);
void to_lower_inplace(char *s);
bool read_line_stdio_echo(char *buf, size_t buflen);
void print_instructions(void);

#endif
