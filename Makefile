NAME	= minishell
CC		= clang
CFLAGS	= -Wall -Wextra -Werror

SRCS	= src/main.c \
		  src/exec_utils.c \
		  src/utils.c \
		  src/handler_build.c \
		  src/tokenisation.c \
		  src/token_utils.c \
		  src/init.c \

OBJS	= $(SRCS:.c=.o)
LIBFT 	= libft/libft.a
all: $(NAME) banner

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

banner:
	@echo ""
	@echo "\033[1;33m███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓\033[0m"
	@echo "\033[1;33m▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒\033[0m"
	@echo "\033[1;33m▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░\033[0m"
	@echo "\033[1;33m▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░\033[0m"
	@echo "\033[1;33m▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒\033[0m"
	@echo "\033[1;33m░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\033[0m"
	@echo "\033[1;33m░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\033[0m"
	@echo "\033[1;33m░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░\033[0m"
	@echo "\033[1;33m       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\033[0m"
	@echo ""

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re