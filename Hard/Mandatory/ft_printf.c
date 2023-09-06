#include "../ft_printf.h"

static inline int	my_format(t_printf *x)
{
	if (x->f == 'c')
		return (my_putchar(va_arg(x->args, int), x));
	else if (x->f == 's')
		return (my_putstring(va_arg(x->args, char *), x));
	else if (x->f == 'd' || x->f == 'i')
		return (my_putint(va_arg(x->args, int), x));
	else if (x->f == 'u')
		return (my_putuint(va_arg(x->args, unsigned int), x));
	else if (x->f == 'p')
		return (my_putpoint(va_arg(x->args, ULL), x));
	else if (x->f == 'x')
		return (my_puthex(va_arg(x->args, unsigned int), HEXLOW, x));
	else if (x->f == 'X')
		return (my_puthex(va_arg(x->args, unsigned int), HEXUP, x));
	else if (x->f == '%')
		return (my_putchar('%', x));
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	t_printf	x;

	x.len = 0;
	va_start(x.args, s);
	while (*s)
	{
		if (*s == '%')
		{
			x.f = *++s;
			if (my_format(&x) == -1)
				return (-1);
		}
		else if (my_putchar(*s, &x) == -1)
			return (-1);
		s++;
	}
	return (va_end(x.args), x.len);
}
