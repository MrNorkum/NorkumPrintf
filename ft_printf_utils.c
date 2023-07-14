/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeles <hkeles@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:15:13 by hkeles            #+#    #+#             */
/*   Updated: 2023/07/11 14:25:01 by hkeles           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	if (!str)
		str = "(null)";
	while (*str)
	{
		if (ft_putchar(*str) == -1)
			return (-1);
		len++;
		str++;
	}
	return (len);
}

int	ft_format_continue(va_list args, char format)
{
	void	*ptr;

	if (format == 'p')
	{
		ptr = va_arg(args, void *);
		if (ptr == NULL)
			return (ft_putstr("0x0"));
		return (ft_itoa_base((uintptr_t)ptr, 16, "0123456789abcdef", 2));
	}
	else if (format == 'x')
		return (ft_itoa_base(va_arg(args, unsigned int),
				16, "0123456789abcdef", 0));
	else if (format == 'X')
		return (ft_itoa_base(va_arg(args, unsigned int),
				16, "0123456789ABCDEF", 0));
	else if (format == '%')
		return (ft_putchar('%'));
	return (-1);
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
	else
		return (ft_format_continue(args, format));
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
		if (ft_putchar(str[tab[i]]) == -1)
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
		if (ft_putchar('-') == -1)
			return (-1);
		len++;
	}
	if (mod == 2 && nbr != 0)
	{
		if (ft_putstr("0x") == -1)
			return (-1);
		len += 2;
	}
	else if (nbr == 0)
	{
		if (ft_putchar('0') == -1)
			return (-1);
		return (1);
	}
	return (ft_itoa_base_continue(nbr, base, str, len));
}
