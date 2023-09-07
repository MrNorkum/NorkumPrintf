#include "../ft_printf.h"

static inline void	haspoint(char *point_adress, t_printf *x)
{
	if (point_adress && x->s > point_adress)
	{
		x->ctrl2 = my_atoi(point_adress + 1, 1, 0, 0);
		x->has_point = 1;
	}
}

static inline int	bonus_format(t_printf *x, char *point_adress)
{
	x->ctrl1 = my_atoi(x->s, 1, 0, 0);
	x->ctrl2 = 0;
	point_adress = ft_strchr(x->s, '.');
	while (*(x->s++))
	{
		if (*(x->s) == 'c' || *(x->s) == '%')
			return (c_function(x));
		if (*(x->s) == 's')
			return (haspoint(point_adress, x), s_function(x));
		if (*(x->s) == 'p')
			return (p_function(x));
		if (*(x->s) == 'u')
			return (haspoint(point_adress, x),
				u_function(x, va_arg(x->args, unsigned int), 0));
		if (*(x->s) == 'd' || *(x->s) == 'i')
			return (haspoint(point_adress, x),
				d_function(x, va_arg(x->args, int), 0));
		if (*(x->s) == 'x' || *(x->s) == 'X')
			return (haspoint(point_adress, x),
				x_function(x, va_arg(x->args, unsigned int), 0));
	}
	return (-1);
}

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
		return (my_putpoint(va_arg(x->args, t_ull), x));
	else if (x->f == 'x')
		return (my_puthex(va_arg(x->args, unsigned int), HEXLOW, x));
	else if (x->f == 'X')
		return (my_puthex(va_arg(x->args, unsigned int), HEXUP, x));
	else if (x->f == '%')
		return (my_putchar('%', x));
	return (bonus_format(x, 0));
}

int	ft_printf(const char *s, ...)
{
	t_printf	x;

	x.len = 0;
	x.s = s;
	x.has_point = 0;
	x.is_c_n = 0;
	va_start(x.args, s);
	while (*x.s)
	{
		if (*(x.s) == '%')
		{
			x.f = *++(x.s);
			x.f2 = *(x.s + 1);
			if (my_format(&x) == -1)
				return (-1);
		}
		else if (my_putchar(*(x.s), &x) == -1)
			return (-1);
		x.s++;
	}
	return (va_end(x.args), x.len);
}
