NAME	= minishell
CC		= clang
CFLAGS	= -Wall -Wextra -Werror

SRCS	= main.c \
		  cwd_utils.c

OBJS	= $(SRCS:.c=.o)
LIBFT 	= libft/libft.a
all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re