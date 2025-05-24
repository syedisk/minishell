NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address,undefined

LIBFT_DIR	= ./lib/libft

INCLUDE		= -I./include -I$(LIBFT_DIR)

LIBS		= -lreadline \
			  -L$(LIBFT_DIR) -lft \

SRC			= src/main.c src/main_utils.c src/main_signals.c src/main_input.c \
			  src/lexer.c src/lexer_utils.c \
			  src/parser.c src/parser_handle_redir.c src/parser_raw_tokens.c src/parser_setup_args.c \
			  src/signal.c src/free_utils.c \
			  src/expander.c src/expander_utils.c src/heredoc.c src/utils.c src/error_handler.c \
			  src/builtins/create_env_list.c src/builtins/env.c \
			  src/builtins/export.c src/builtins/export_utils.c src/builtins/unset.c src/builtins/pwd.c \
			  src/builtins/cd.c src/builtins/echo.c src/builtins/echo_utils.c src/builtins/exit.c \
			  src/exec.c src/exec_utils4.c src/exec_builtin.c src/exec_utils.c src/exec_utils1.c src/exec_utils2.c \
			  src/exec_utils3.c src/exec_utils5.c src/exec_utils6.c src/exec_utils7.c \

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

.PHONY: all clean fclean re
