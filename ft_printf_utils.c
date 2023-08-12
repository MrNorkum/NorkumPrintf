#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	len;

	len = -1;
	if (!str)
		str = "(null)";
	while (str[++len])
		if (write(1, &str[len], 1) == -1)
			return (-1);
	return (len);
}

int	ft_itoa_base_continue(uintptr_t nbr, int base, char *str, int len)
{
	int	tab[100];
	int	i;

	i = 0;
	while (nbr)
	{
		tab[i++] = nbr % base;
		nbr /= base;
	}
	while (i--)
	{
		len++;
		if (write(1, &str[tab[i]], 1) == -1)
			return (-1);
	}
	return (len);
}
