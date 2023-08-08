NAME = libcvec.a

_SRC =  cvec.c

_OBJ = $(_SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re test
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

test:
	echo "cvec test"
