#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>

int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_itoa_base(uintptr_t nbr, int base, char *str, int mod);
int		ft_format(va_list args, char format);

#endif
