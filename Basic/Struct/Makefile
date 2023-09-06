NAME = libftprintf.a
RM = rm -rf
CC = gcc
FLAG = -Wall -Wextra -Werror
CMPL = $(CC) $(FLAG) -c
SRC = 	./ft_printf.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@$(CMPL) $(SRC)
	@ar rc $(NAME) $(OBJ)
clean:
	@$(RM) $(OBJ)
fclean : clean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
