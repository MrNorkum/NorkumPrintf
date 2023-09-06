#include "../ft_printf.h"

int	my_putuint(unsigned long n, t_printf *x)
{
	int		arr[100];
	int		i;
	char	*nbr;

	i = 0;
	nbr = DEC;
	if (!n)
		return (my_putchar('0', x));
	while (n)
	{
		arr[i++] = n % 10;
		n /= 10;
	}
	while (i--)
		if (my_putchar(nbr[arr[i]], x) == -1)
			return (-1);
	return (1);
}

int	my_puthex(unsigned long n, char *hex, t_printf *x)
{
	int		arr[100];
	int		i;

	i = 0;
	if (!n)
		return (my_putchar('0', x));
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

int	my_putpoint(ULL n, t_printf *x)
{
	int			arr[100];
	char		*hex;
	int			i;

	i = 0;
	hex = HEXLOW;
	if (my_putstring("0x", x) == -1)
		return (-1);
	if (!n)
		return (my_putchar('0', x));
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
