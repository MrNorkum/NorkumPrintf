#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

# define DEC "0123456789"
# define HEXLOW "0123456789abcdef"
# define HEXUP "0123456789ABCDEF"

typdef unsigned long long  t_ull;

typedef struct s_printf
{
	va_list		args;
	char		f;
	char		f2;
	int			len;
	const char	*s;
	int			ctrl1;
	int			ctrl2;
	int			has_point;
	int			tmp_has_point;
	int			is_c_n;
	int			is_negative;
	int			is_space_zero;
	int			is_minus_plus;
	int			is_sharp_zero;
	int			truth;
	int			truth2;
	int			truth3;
	int			truth4;
	int			truth5;
}		t_printf;

int		my_putchar(char c, t_printf *x);
int		my_putstring(char *s, t_printf *x);
int		my_putint(long n, t_printf *x);
int		my_putuint(unsigned long n, t_printf *x);
int		my_putpoint(t_ull n, t_printf *x);
int		my_puthex(unsigned long n, char *hex, t_printf *x);
int		ft_printf(const char *s, ...);

int		c_function(t_printf *x);
int		s_function(t_printf *x);
int		p_function(t_printf *x);
int		u_function(t_printf *x, unsigned int n, int len);
int		d_function(t_printf *x, long n, int len);
int		x_function(t_printf *x, unsigned int n, int len);
int		nbrlen(int n);
int		nbrulen(t_ull n, int base);
int		ft_strlen(char *str);
char	*ft_strchr(const char *s, int c);
int		my_atoi(const char *str, int sign, int res, int mod);

#endif
