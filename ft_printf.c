#include "ft_printf.h"
#include <unistd.h>

int	ft_putchar(char c)
{
	return(write(1, &c, 1));
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
		else if (ft_putchar(*str++) == -1)
			return (-1);
		len += tmp;
	}
	va_end(args);
	return (len);
}
