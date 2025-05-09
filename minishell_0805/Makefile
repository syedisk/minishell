NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror -g

LIBFT_DIR	= ./lib/libft

INCLUDE		= -I./include -I$(LIBFT_DIR)

LIBS		= -lreadline \
			  -L$(LIBFT_DIR) -lft \

SRC			= src/main.c src/lexer.c src/parser.c src/exec.c src/exec_utils.c src/signal.c src/free_utils.c \
			  src/expander.c src/heredoc.c src/utils.c src/error_handler.c \
			  src/builtins/env_utils.c src/builtins/env.c \
			  src/builtins/export.c src/builtins/unset.c \

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

.PHONY: all clean fclean re test
