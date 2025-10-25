MAKEFLAGS += -s

NAME	= minishell
CC		= clang
CFLAGS	= -Wall -Wextra -Werror

SRCS	= src/main.c \
		  src/utils/global/utility.c \
		  src/utils/global/h_utility.c \
		  src/utils/global/path.c \
		  src/parse/parse_input/p_cmds.c \
		  src/parse/parse_input/p_helper.c \
		  src/parse/parse_validate/v_input.c \
		  src/parse/parse_validate/v_start.c \
		  src/parse/parse_input/p_args.c \
		  src/utils/init/init_struct.c \
		  src/utils/init/init_envp.c \
		  src/utils/main/readline.c \
		  src/exec/exec_custom/select.c \
		  src/exec/exec_custom/cmd_list/cd.c \
		  src/exec/exec_custom/cmd_list/echo.c \
		  src/exec/exec_custom/cmd_list/env.c \
		  src/exec/exec_custom/cmd_list/exit.c \
		  src/exec/exec_custom/cmd_list/export.c \
		  src/exec/exec_custom/cmd_list/pwd.c \
		  src/exec/exec_custom/cmd_list/unset.c \
		  src/parse/handle_input.c \
		  src/exec/exec_main/pre_exec.c \
		  src/exec/exec_main/handle_exec.c \
		  src/exec/exec_helper/h_pre_exec.c \
		  src/exec/exec_helper/h_pre_exec_extra.c \
		  src/exec/exec_helper/h_exec.c \
		  src/exec/exec_main/execute.c \
		  src/exec/redirection/r_basic.c \
		  src/exec/redirection/r_heredoc.c \
		  src/signal/init_signal.c \
		  src/utils/free/exit.c \
		  src/utils/free/newline.c \
		  src/utils/free/in_readline.c \
		  src/utils/error/send_error.c \
		  src/utils/error/error_custom.c \
		  src/checker/c_exec/check_x.c \
		  src/checker/c_exec/check_x_extra.c \
		  src/checker/c_exec/is_x.c\
		  src/checker/c_parse/check_x.c \
		  src/checker/c_parse/is_x.c

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
	@clear
	@echo ""
	@echo "\033[0;34m  ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \033[0m"
	@echo "\033[0;34m  ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \033[0m"
	@echo "\033[0;34m  ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \033[0m"
	@echo "\033[0;34m  ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \033[0m"
	@echo "\033[0;34m  ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\033[0m"
	@echo "\033[0;34m  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\033[0m"
	@echo ""
	@echo "\033[1;32m   	=== Type ./minishell to run the shell ===\033[0m"
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
