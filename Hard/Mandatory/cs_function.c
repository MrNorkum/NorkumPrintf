#include "../ft_printf.h"
#include <unistd.h>

int	my_putchar(char c, t_printf *x)
{
	return (x->len++, write(1, &c, 1));
}

int	my_putstring(char *s, t_printf *x)
{
	if (!s)
		s = "(null)";
	while (*s)
		if (my_putchar(*s++, x) == -1)
			return (-1);
	return (1);
}
