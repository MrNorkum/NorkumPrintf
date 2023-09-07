#include "../ft_printf.h"

int	p_function(t_printf *x)
{
	int		i;
	void	*p;
	int		len;

	p = va_arg(x->args, t_ull);
	len = nbrulen(p, 16) + 2;
	i = -1;
	if (x->ctrl1 > 0)
		while (++i < x->ctrl1 - len)
			if (my_putchar(' ', x) == -1)
				return (-1);
	if (my_putpoint(p, x) == -1)
		return (-1);
	if (x->ctrl1 < 0)
		while (++i < -x->ctrl1 - len)
			if (my_putchar(' ', x) == -1)
				return (-1);
	return (1);
}

int	u_function(t_printf *x, unsigned int n, int len)
{
	len = nbrulen(n, 10);
	if (x->f == '0' && !x->has_point)
		x->ctrl2 = x->ctrl1 * !(x->ctrl1 <= len);
	x->ctrl1 = !(x->f == '0' && !x->has_point) * x->ctrl1;
	x->is_c_n = (x->ctrl1 < 0);
	x->ctrl1 += -2 * x->is_c_n * x->ctrl1 + (!x->ctrl2 && !n && x->has_point)
		- (x->ctrl2 > len) * (x->ctrl2 - len);
	x->ctrl1 -= (x->ctrl1 < 0) * x->ctrl1;
	x->has_point = !(x->ctrl2 > len) * x->has_point;
	x->ctrl2 -= (x->ctrl2 > len) * len;
	while (!x->is_c_n && x->ctrl1-- > len)
		if (my_putchar(' ', x) == -1)
			return (-1);
	while (!x->has_point && x->ctrl2--)
		if (my_putchar('0', x) == -1)
			return (-1);
	if ((x->ctrl2 || n || !x->has_point) && my_putuint(n, x) == -1)
		return (-1);
	while (x->is_c_n && x->ctrl1-- > len)
		if (my_putchar(' ', x) == -1)
			return (-1);
	return (x->has_point = 0, x->is_c_n = 0, 1);
}

static inline int	my_putbhex(unsigned long n, t_printf *x)
{
	int		arr[100];
	int		i;
	char	*hex;

	i = 0;
	if (*(x->s) == 'x')
		hex = HEXLOW;
	else
		hex = HEXUP;
	if (!n)
		arr[i++] = 0;
	while (n)
	{
		arr[i++] = n % 16;
		n /= 16;
	}
	while (i--)
		if (my_putchar(hex[arr[i]], x) == -1)
			return (-1);
	return (1);
}

static inline int	x_print(t_printf *x, unsigned int n, int len)
{
	while (!x->is_c_n && x->ctrl1-- > len)
		if (my_putchar(' ', x) == -1)
			return (-1);
	if ((x->f == '#' || x->f2 == '#') && n
		&& (my_putchar('0', x) == -1 || my_putchar(*(x->s), x) == -1))
		return (-1);
	while (!x->has_point && x->ctrl2--)
		if (my_putchar('0', x) == -1)
			return (-1);
	if ((x->ctrl2 || n || !x->has_point) && my_putbhex(n, x) == -1)
		return (-1);
	while (x->is_c_n && x->ctrl1-- > len)
		if (my_putchar(' ', x) == -1)
			return (-1);
	return (x->has_point = 0, x->is_c_n = 0, 1);
}

int	x_function(t_printf *x, unsigned int n, int len)
{
	x->tmp_has_point = x->has_point;
	x->is_sharp_zero = (x->f2 == '0' && x->f == '#')
		|| (x->f == '0' && x->f2 == '#');
	len = nbrulen(n, 16);
	if ((x->f == '0' || x->is_sharp_zero) && !x->has_point)
		x->ctrl2 = x->ctrl1 * !(x->ctrl1 <= len);
	x->ctrl1 = !((x->f == '0' || x->is_sharp_zero) && !x->has_point) * x->ctrl1;
	x->is_c_n = (x->ctrl1 < 0);
	x->ctrl1 += -2 * x->is_c_n * x->ctrl1 + (!x->ctrl2 && !n && x->has_point)
		- (x->ctrl2 > len) * (x->ctrl2 - len);
	x->ctrl1 -= (x->ctrl1 < 0) * x->ctrl1
		+ ((x->f == '#' || x->f2 == '#') && n) * 2;
	x->has_point = !(x->ctrl2 > len) * x->has_point;
	x->ctrl2 -= (x->ctrl2 > len) * len + 2
		* x->is_sharp_zero * !x->tmp_has_point * (n != 0);
	x->ctrl2 = !(x->ctrl2 < 0) * x->ctrl2;
	return (x_print(x, n, len));
}
