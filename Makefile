NAME	= minishell
CC		= clang
CFLAGS	= -pthread -Wall -Wextra -Werror

SRCS	= main.c \
		  utils.c \

OBJS	= $(SRCS:.c=.o)
all: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make clean

re: fclean all

.PHONY: all clean fclean re