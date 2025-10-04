NAME	= minishell
CC		= clang
CFLAGS	= -Wall -Wextra -Werror

SRCS	= src/main.c \
		  src/parse/select_run.c \
		  src/utils/utils_trash.c \
		  src/parse/tokenisation.c \
		  src/utils/token_utils.c \
		  src/utils/init.c \
		  src/exec_built/handler_built.c \
		  src/exec_built/find_built.c \
		  src/exec_bin/run_bin.c \
		  src/exec_bin/prerun_bin.c

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