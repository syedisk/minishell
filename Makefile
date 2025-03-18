NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror -g

LIBFT_DIR	= ./lib/libft

INCLUDE		= -I./include -I$(LIBFT_DIR)

LIBS		= -lreadline \
			  -L$(LIBFT_DIR) -lft \

SRC			= src/main.c

OBJ			= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) CFLAGS="$(CFLAGS)"
	$(MAKE) -C $(LIBFT_DIR) bonus CFLAGS="$(CFLAGS)"
	cc $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	cc $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

test_lexer:
	cc $(CFLAGS) $(INCLUDE) test/test_lexer.c src/lexer.c -o test_lexer

.PHONY: all clean fclean re test
