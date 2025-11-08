/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_heredoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:10:03 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/01 11:28:01 by astrelci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	restore_terminal_settings(t_data *d)
{
	struct termios	term;

	if (d && d->term_saved)
		tcsetattr(STDIN_FILENO, TCSANOW, &d->original_term);
	else if (tcgetattr(STDIN_FILENO, &term) != -1)
	{
		term.c_lflag |= (ECHO | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void	heredoc_cleanup_on_failure(t_heredoc_ctx *ctx, int error_state,
		int reset_terminal)
{
	if (ctx->fd[0] >= 0)
		close(ctx->fd[0]);
	if (ctx->stdin_backup >= 0)
		close(ctx->stdin_backup);
	if (reset_terminal)
	{
		restore_terminal_settings(ctx->d);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	signal(SIGINT, handler_ctrl_c);
	ctx->d->error_state = error_state;
}

int	heredoc_parent_should_abort(t_heredoc_ctx *ctx, int status,
		int interrupted)
{
	if (interrupted)
	{
		heredoc_cleanup_on_failure(ctx, 130, 1);
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		heredoc_cleanup_on_failure(ctx, 1, 0);
		return (1);
	}
	return (0);
}

static int	handle_line(int fd_write, char *line, t_data *d, int should_expand)
{
	int		is_dquote;
	char	*expanded;

	if (should_expand && ft_strchr(line, '$'))
	{
		is_dquote = 0;
		expanded = expand_arg(line, d, &is_dquote);
		if (expanded)
		{
			ft_putstr_fd(expanded, fd_write);
			free(expanded);
		}
		ft_putstr_fd("\n", fd_write);
		return (1);
	}
	ft_putstr_fd(line, fd_write);
	ft_putstr_fd("\n", fd_write);
	return (0);
}

int	heredoc_read_loop(int fd_write, char *delimiter, t_data *d,
		int should_expand)
{
	char	*res;

	while (1)
	{
		res = readline("> ");
		if (!res)
		{
			print_error("here-document delimited by end-of-file", "warning");
			return (1);
		}
		if (!ft_strncmp(res, delimiter, ft_strlen(delimiter) + 1))
		{
			free(res);
			return (0);
		}
		if (!handle_line(fd_write, res, d, should_expand))
			free(res);
	}
}
