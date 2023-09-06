#include "ft_printf.h"

int	nbrlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	if (!n)
		return (1);
	while ((n > 0 || n < 0) && ++len)
		n /= 10;
	return (len);
}

int	nbrulen(ULL n, int base)
{
	int	len;

	len = 0;
	if (!n)
		return (1);
	while (++len && n)
		n /= base;
	return (--len);
}

int	my_atoi(const char *str, int sign, int res, int mod)
{
	if (((9 <= *str && *str <= 13) || *str == 32 || *str == 48 || *str == 35)
		&& mod == 0)
		return (my_atoi(str + 1, 1, 0, 0));
	if (*str == 32 || *str == 43 || *str == 35)
		return (my_atoi(str + 1, sign, 0, 0));
	if (*str == 43 && mod == 0)
		return (my_atoi(str + 1, 1, 0, 1));
	if (*str == 45)
		return (my_atoi(str + 1, -1, 0, 1));
	if ('0' <= *str && *str <= '9')
		return (my_atoi(str + 1, sign, res * 10 + *str - 48, 1));
	return (res * sign);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}
