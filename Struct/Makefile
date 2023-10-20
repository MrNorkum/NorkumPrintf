NAME = libftprintf.a
AR = ar rc
CC = gcc
FLAG = -Wall -Wextra -Werror
CMPL = $(CC) $(FLAG) -c
RM = rm -rf
MKDIR = mkdir -p
OBJDIR = OBJECT
SRC = my_printf.c

OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))

$(OBJDIR)/%.o:  %.c
	@$(MKDIR) $(OBJDIR)
	@$(CMPL) $< -o $@

all: $(NAME)
a: all

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

c: clean
clean:
	@$(RM) $(OBJDIR)

f: fclean
fclean : clean
	@$(RM) $(NAME)

re: fclean all

r:
	@make re
	@make clean

.PHONY: all clean fclean re
