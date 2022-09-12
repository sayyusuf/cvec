NAME = argv.a

_SRC = argv.c

_OBJ = $(_SRC:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror 

.PHONY: all clean fclean re bonus
all: $(NAME)

$(NAME): $(_OBJ)
	ar -rcs $@ $^
	ranlib $@
%.o: %.c
	$(CC)  $(FLAGS) -I./ -c $< -o $@

clean : 
	rm -f $(_OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all
