#include "ft_printf.h"
#include <unistd.h>

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

int	ft_printf(const char *str, ...)
{
	int	len;
	int	tmp;
	va_list	args;

	len = 0;
	va_start(args, str);
	while (*str)
	{
		tmp = 1;
		if (*str == '%')
		{
			tmp = ft_format(args, *++str);
			if (tmp == -1)
				return (-1);
		}
		else if (write(1, str++, 1) == -1)
			return (-1);
		len += tmp;
	}
	va_end(args);
	return (len);
}
