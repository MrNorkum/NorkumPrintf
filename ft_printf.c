#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

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
		else if (write(1, str, 1) == -1)
			return (-1);
		str++;
		len += tmp;
	}
	va_end(args);
	return (len);
}
