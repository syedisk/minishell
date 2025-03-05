NAME = libftprintf.a

SRC = ft_printf.c \
      ft_putchar.c ft_putstr_pf.c ft_putnbr.c ft_tohex.c ft_putnbr_unsigned.c\
	  handle_int.c handle_str.c handle_char.c handle_ptr.c handle_u.c handle_hex.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	cc $(CFLAGS) test.c -L. -lftprintf -o test

run: test
	./test

.PHONY: all clean fclean re test run
