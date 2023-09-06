#include "../ft_printf.h"

int	my_putint(long n, t_printf *x)
{
	int		arr[100];
	int		i;
	char	*nbr;

	i = 0;
	nbr = DEC;
	if (!n)
		return (my_putchar('0', x));
	if (n < 0 && my_putchar('-', x) == -1)
		return (-1);
	if (n < 0)
		n = -n;
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
