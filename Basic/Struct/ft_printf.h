#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

# define DEC "0123456789"
# define HEXLOW "0123456789abcdef"
# define HEXUP "0123456789ABCDEF"

typdef unsigned long long  t_ull;

typedef struct s_printf
{
	va_list		args;
	char		f;
	int			len;
}		t_printf;

int	ft_printf(const char *s, ...);

#endif
