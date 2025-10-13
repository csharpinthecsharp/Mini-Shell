MAKEFLAGS += -s

NAME	= minishell
CC		= clang
CFLAGS	= -Wall -Wextra -Werror

SRCS	= src/main.c \
		  src/utils/utils_trash.c \
		  src/parse/parsing.c \
		  src/parse/validate_input.c \
		  src/parse/parsing_utils.c \
		  src/utils/init.c \
		  src/exec/exec_built/find_built.c \
		  src/exec/exec_built/cd.c \
		  src/exec/exec_built/echo.c \
		  src/exec/exec_built/env.c \
		  src/exec/exec_built/exit.c \
		  src/exec/exec_built/export.c \
		  src/exec/exec_built/pwd.c \
		  src/exec/exec_built/unset.c \
		  src/parse/handle_input.c \
		  src/exec/execution.c \
		  src/exec/redirection.c \
		  src/exec/exec_utils.c \
		  src/signal/init_signal.c \
		  src/utils/memory_alloc.c \
		  src/utils/free.c \
		  rl.c

OBJS	= $(SRCS:.c=.o)
LIBFT 	= libft/libft.a
all: before $(NAME) banner

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline
before:
	@echo "\033[0;32mCompiling..\033[0m"
banner:
	@echo ""
	@echo "\033[1;34m ██▒   █▓ ▄▄▄▄    ▄▄▄        ██████  ██░ ██ \033[0m"
	@echo "\033[1;34m▓██░   █▒▓█████▄ ▒████▄    ▒██    ▒ ▓██░ ██▒\033[0m"
	@echo "\033[1;34m ▓██  █▒░▒██▒ ▄██▒██  ▀█▄  ░ ▓██▄   ▒██▀▀██░\033[0m"
	@echo "\033[1;34m  ▒██ █░░▒██░█▀  ░██▄▄▄▄██   ▒   ██▒░▓█ ░██ \033[0m"
	@echo "\033[1;34m   ▒▀█░  ░▓█  ▀█▓ ▓█   ▓██▒▒██████▒▒░▓█▒░██▓\033[0m"
	@echo "\033[0;32m   ░ ▐░  ░▒▓███▀▒ ▒▒   ▓▒█░▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒\033[0m"
	@echo "\033[0;32m   ░ ░░  ▒░▒   ░   ▒   ▒▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░\033[0m"
	@echo "\033[0;32m     ░░   ░    ░   ░   ▒   ░  ░  ░   ░  ░░ ░\033[0m"
	@echo "\033[0;32m      ░   ░            ░  ░      ░   ░  ░  ░\033[0m"
	@echo "\033[0;32m     ░         ░\033[0m"
	@echo ""

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	@echo "\033[0;31mCompiled files have been removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re