#include "../ft_printf.h"

static inline int	my_putbstring(char *s, t_printf *x, int len)
{
	if (!s)
		s = "(null)";
	while (len--)
		if (my_putchar(*s++, x) == -1)
			return (-1);
	return (1);
}

int	c_function(t_printf *x)
{
	int		i;
	char	c;

	if (*(x->s) == 'c')
		c = va_arg(x->args, int);
	else
		c = '%';
	i = -1;
	if (x->ctrl1 > 0)
		while (++i < x->ctrl1 - 1)
			if (my_putchar(' ', x) == -1)
				return (-1);
	if (my_putchar(c, x) == -1)
		return (-1);
	if (x->ctrl1 < 0)
		while (++i < -x->ctrl1 - 1)
			if (my_putchar(' ', x) == -1)
				return (-1);
	return (1);
}

int	s_function(t_printf *x)
{
	int		i;
	int		len;
	char	*str;

	str = va_arg(x->args, char *);
	if (str)
		len = ft_strlen(str);
	else
		len = 6;
	if (x->has_point && len > x->ctrl2)
		len = x->ctrl2;
	x->has_point = 0;
	i = -1;
	if (x->ctrl1 > 0)
		while (++i < x->ctrl1 - len)
			if (my_putchar(' ', x) == -1)
				return (-1);
	if (my_putbstring(str, x, len) == -1)
		return (-1);
	if (x->ctrl1 < 0)
		while (++i < -x->ctrl1 - len)
			if (my_putchar(' ', x) == -1)
				return (-1);
	return (1);
}
