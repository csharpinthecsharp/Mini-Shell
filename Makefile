MAKEFLAGS += -s

NAME	= minishell
CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g

SRCS	= src/main.c \
		  src/utils/global/utils_trash.c \
		  src/parse/parse_input/p_cmds.c \
		  src/parse/parse_input/p_helper.c \
		  src/parse/parse_validate/v_input.c \
		  src/parse/parse_validate/v_start.c \
		  src/parse/parse_input/p_args.c \
		  src/utils/init/init_struct.c \
		  src/utils/init/init_envp.c \
		  src/utils/main/readline.c \
		  src/exec/find_built.c \
		  src/exec/exec_custom/cd.c \
		  src/exec/exec_custom/echo.c \
		  src/exec/exec_custom/env.c \
		  src/exec/exec_custom/exit.c \
		  src/exec/exec_custom/export.c \
		  src/exec/exec_custom/pwd.c \
		  src/exec/exec_custom/unset.c \
		  src/parse/handle_input.c \
		  src/exec/execution.c \
		  src/exec/redirection/r_basic.c \
		  src/exec/redirection/r_heredoc.c \
		  src/exec/exec_utils.c \
		  src/signal/init_signal.c \
		  src/utils/malloc/allocation.c \
		  src/utils/malloc/a_exec.c \
		  src/utils/malloc/a_parse.c \
		  src/utils/free/exit.c \
		  src/utils/free/newline.c \
		  src/utils/error/send_error.c

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
	@echo "\033[0;32m		.__       .__       .__           .__  .__   \033[0m"
	@echo "\033[0;32m	  _____ |__| ____ |__| _____|  |__   ____ |  | |  |  \033[0m"
	@echo "\033[0;32m	 /     \|  |/    \|  |/  ___/  |  \_/ __ \|  | |  |  \033[0m"
	@echo "\033[0;32m	|  Y Y  \  |   |  \  |\___ \|   Y  \  ___/|  |_|  |__\033[0m"
	@echo "\033[0;32m	|__|_|  /__|___|  /__/____  >___|  /\___  >____/____/\033[0m"
	@echo "\033[0;32m	      \/        \/        \/     \/     \/          \033[0m"
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
