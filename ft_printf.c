/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeles <hkeles@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 02:09:13 by hkeles            #+#    #+#             */
/*   Updated: 2023/07/11 14:19:13 by hkeles           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_printf_continue(const char *str, va_list args)
{
	int	len;
	int	tmp;

	len = 0;
	tmp = 0;
	while (*str != '\0')
	{
		tmp = 1;
		if (*str == '%')
		{
			str++;
			tmp = ft_format(args, *str);
			if (tmp == -1)
				return (-1);
		}
		else if (ft_putchar(*str) == -1)
			return (-1);
		len += tmp;
		str++;
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	args;

	va_start(args, str);
	len = ft_printf_continue(str, args);
	va_end(args);
	return (len);
}
