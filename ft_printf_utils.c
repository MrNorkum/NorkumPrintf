#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>

int ft_putchar(char c)
{
  return (write(1, &c, 1));
}

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

int	ft_format(va_list args, char format)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'u')
		return (ft_itoa_base(va_arg(args, unsigned int), 10, "0123456789", 0));
	else if (format == 'd' || format == 'i')
		return (ft_itoa_base(va_arg(args, int), 10, "0123456789", 1));
	else if (format == 'p')
		return (ft_itoa_base(va_arg(args, uintptr_t), 
			16, "0123456789abcdef", 2));
	else if (format == 'x')
		return (ft_itoa_base(va_arg(args, unsigned int),
			16, "0123456789abcdef", 0));
	else if (format == 'X')
		return (ft_itoa_base(va_arg(args, unsigned int),
			16, "0123456789ABCDEF", 0));
	else if (format == '%')
		return (write(1, "%", 1));
	return (-1);
}
