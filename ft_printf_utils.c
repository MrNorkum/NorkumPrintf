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

int	ft_itoa_base(uintptr_t nbr, int base, char *str, int mod)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (mod == 1 && (int)nbr < 0)
	{
		nbr *= -1;
		if (write(1, "-", 1) == -1)
			return (-1);
		len++;
	}
	if (mod == 2)
	{
		if (ft_putstr("0x") == -1)
			return (-1);
		len += 2;
	}
	if (nbr == 0)
		return (len + write(1, "0", 1));
	return (ft_itoa_base_continue(nbr, base, str, len));
}
