#include "../ft_printf.h"

static inline void	d_extractrl(t_printf *x)
{
	int	i;

	i = 1;
	if (x->f == '-')
	{
		while (*(x->s - i) != '%')
		{
			x->is_minus_plus = *(x->s - (i++)) == '+';
			if (x->is_minus_plus)
			{
				x->f = '+';
				break ;
			}
		}
	}
	else if (x->f == '+')
	{
		while (*(x->s - i) != '%')
		{
			x->is_minus_plus = *(x->s - (i++)) == '-';
			if (x->is_minus_plus)
				break ;
		}
	}
}

static inline void	d_ctrl(t_printf *x, long n, int len)
{
	x->is_space_zero = 0;
	d_extractrl(x);
	x->truth = (len <= x->ctrl2);
	x->truth2 = (len == x->ctrl2) * (n < 0);
	if (x->f2 == '+' && x->has_point)
		x->f = x->f2;
	if (x->f == '+' && x->f2 == '0' && !x->has_point)
	{
		x->f2 = '+';
		x->f = '0';
	}
	if (x->f == '-' && x->f2 == ' ')
	{
		x->f2 = '-';
		x->f = ' ';
	}
	if ((x->f2 == '0' && x->f == ' ') || (x->f2 == ' ' && x->f == '0'))
	{
		x->f2 = (x->f = '0');
		x->is_space_zero = 1;
	}
	x->truth3 = ((x->ctrl1 <= x->ctrl2) || x->ctrl1 <= len)
		* (x->f == ' ') * (!(n == 0 && x->ctrl1 > x->ctrl2) || !x->has_point);
	x->tmp_has_point = x->has_point;
}

static inline int	d_print1(t_printf *x, int len)
{
	if (x->truth3 * (!x->is_negative) || (x->is_c_n && x->f2 == ' ')
		|| (x->is_space_zero && !x->tmp_has_point && !x->is_negative))
	{
		if (my_putchar(' ', x) == -1)
			return (-1);
	}
	else if (x->is_space_zero && x->truth5
		&& x->tmp_has_point && my_putchar(' ', x) == -1)
		return (-1);
	while (!x->is_c_n && x->ctrl1-- - x->is_negative
		* x->tmp_has_point * x->truth - x->truth4 > len)
		if (my_putchar(' ', x) == -1)
			return (-1);
	if (x->is_negative && my_putchar('-', x) == -1)
		return (-1);
	else if (!x->is_negative && x->f == '+' && my_putchar('+', x) == -1)
		return (-1);
	if (x->truth2 && my_putchar('0', x) == -1)
		return (-1);
	return (1);
}

static inline int	d_print2(t_printf *x, long n, int len)
{
	x->ctrl2 -= (x->f2 == '+' && x->f != '+' && !x->is_negative)
		+ (x->is_space_zero && !x->tmp_has_point && !x->is_negative);
	x->ctrl2 += (x->ctrl2 < 0);
	if (x->f2 == '+' && x->f != '+' && !x->is_negative
		&& my_putchar('+', x) == -1)
		return (-1);
	while (!x->has_point && x->ctrl2-- + x->is_negative * x->tmp_has_point)
		if (my_putchar('0', x) == -1)
			return (-1);
	if ((x->ctrl2 || n || !x->has_point) && my_putint(n, x) == -1)
		return (-1);
	x->ctrl1 -= (x->is_c_n && !x->is_negative && (x->f == ' ' || x->f2 == ' '))
		+ x->is_minus_plus * !x->is_negative;
	while (x->is_c_n
		&& x->ctrl1-- - x->is_negative * x->tmp_has_point * x->truth > len)
		if (my_putchar(' ', x) == -1)
			return (-1);
	return (x->has_point = 0, x->is_c_n = 0, 1);
}

int	d_function(t_printf *x, long n, int len)
{
	len = nbrlen(n);
	d_ctrl(x, n, len);
	x->is_negative = (n < 0);
	x->truth4 = (x->ctrl1 > x->ctrl2) * (x->f == '+') * !x->is_negative;
	x->truth5 = ((x->ctrl2 >= x->ctrl1) || (x->ctrl1 <= len && n))
		&& (!x->is_negative);
	n = (n < 0) * -n + !(n < 0) * n;
	if (x->f == '0' && !x->has_point)
		x->ctrl2 = x->ctrl1 * !(x->ctrl1 <= len);
	x->ctrl1 = !(x->f == '0' && !x->has_point) * x->ctrl1;
	x->is_c_n = (x->ctrl1 < 0);
	x->ctrl1 += -2 * x->is_c_n * x->ctrl1 + (!x->ctrl2 && !n && x->has_point)
		- (x->ctrl2 > len) * (x->ctrl2 - len);
	x->ctrl1 -= (x->ctrl1 < 0) * x->ctrl1;
	x->has_point = !(x->ctrl2 > len) * x->has_point;
	x->ctrl2 -= (x->ctrl2 > len) * len;
	if (d_print1(x, len) == -1)
		return (-1);
	return (d_print2(x, n, len));
}
