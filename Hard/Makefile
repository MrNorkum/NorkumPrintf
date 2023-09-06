NAME = libftprintf.a
RM = rm -rf
CC = gcc
FLAG = -Wall -Wextra -Werror
CMPL = $(CC) $(FLAG) -c
OBJ = *.o

SRC = 	Mandatory/ft_printf.c	\
		Mandatory/cs_function.c	\
		Mandatory/di_function.c	\
		Mandatory/pux_function.c

BSRC =	Bonus/ft_printf_bonus.c		\
		Mandatory/cs_function.c		\
		Bonus/cs_bonus.c			\
		Mandatory/di_function.c		\
		Bonus/di_bonus.c			\
		Mandatory/pux_function.c	\
		Bonus/pux_bonus.c			\
		Bonus/libft_bonus.c

all: $(NAME)

$(NAME):
	@$(CMPL) $(SRC)
	@ar rc $(NAME) $(OBJ)

bonus:
	@$(CMPL) $(BSRC)
	@ar rc $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re: fclean all

bre: fclean bonus

.PHONY: all bonus clean fclean re
