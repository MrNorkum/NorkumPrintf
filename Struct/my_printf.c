#include "my_printf.h"

static int	my_putchar(char c, printf_t *x)
{
	return (x->len++, write(1, &c, 1));
}

static int	my_putstr(char *s, printf_t *x)
{
	if (!s)
		s = "(null)";
	while (*s)
		if (my_putchar(*s++, x) == -1)
			return (-1);
	return (1);
}

static int	my_itoa(u_int64_t n, int base, char *s, printf_t *x)
{
	int	arr[15];
	int	mod;
	int	i;

	mod = (x->f == 'd' || x->f == 'i') + 2 * (x->f == 'p');
	i = 0;
	if (mod == 1 && (int)n < 0)
	{
		n = -n;
		if (my_putchar('-', x) == -1)
			return (-1);
	}
	if (mod == 2 && my_putstr("0x", x) == -1)
		return (-1);
	if (!n && my_putchar('0', x) == -1)
		return (-1);
	while (n)
	{
		arr[i++] = n % base;
		n /= base;
	}
	while (i--)
	    if (my_putchar(s[arr[i]], x) == -1)
			return (-1);
	return (1);
}

static int	my_format(printf_t *x)
{
	if (x->f == 'c')
		return (my_putchar(va_arg(x->args, int), x));
	else if (x->f == 's')
		return (my_putstr(va_arg(x->args, char *), x));
	else if (x->f == 'd' || x->f == 'i')
		return (my_itoa(va_arg(x->args, int), 10, DEC, x));
	else if (x->f == 'u')
		return (my_itoa(va_arg(x->args, unsigned int), 10, DEC, x));
	else if (x->f == 'x')
		return (my_itoa(va_arg(x->args, unsigned int), 16, HEXLOW, x));
	else if (x->f == 'X')
		return (my_itoa(va_arg(x->args, unsigned int), 16, HEXUP, x));
	else if (x->f == 'p')
		return (my_itoa(va_arg(x->args, u_int64_t), 16, HEXLOW, x));
	else if (x->f == '%')
		return (my_putchar('%', x));
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	printf_t	x;

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

