#ifndef MY_PRINTF_H
# define MY_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

# define DEC "0123456789"
# define HEXLOW "0123456789abcdef"
# define HEXUP "0123456789ABCDEF"

typedef struct printf_s
{
	va_list		args;
	char		f;
	int			len;
}		printf_t;

int	my_printf(const char *s, ...);

#endif
