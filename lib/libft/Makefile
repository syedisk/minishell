NAME = libft.a

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
      ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
      ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
      ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
      ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
      ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
      ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
      ft_putendl_fd.c ft_putnbr_fd.c get_next_line_bonus.c \
	  ft_strndup.c ft_strcmp.c

	
BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	    ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	    ft_lstmap.c

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

ALL_OBJ = $(OBJ) $(BONUS_OBJ)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(ALL_OBJ)
	ar rcs $(NAME) $(ALL_OBJ)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	cc $(CFLAGS) test.c -L. -lft -o test

run: test
	./test

.PHONY: all clean fclean re test run bonus
