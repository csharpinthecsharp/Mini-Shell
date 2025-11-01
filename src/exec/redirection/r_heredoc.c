/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:16:18 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/31 22:24:12 by astrelci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static pid_t	heredoc_pid_create(int *heredoc, int *stdin)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(heredoc[0]);
		close(heredoc[1]);
		close(*stdin);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	heredoc_error_handler(int *heredoc, int *stdin)
{
	if (pipe(heredoc) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	*stdin = dup(STDIN_FILENO);
	if (*stdin == -1)
	{
		perror("dup");
		close(heredoc[0]);
		close(heredoc[1]);
		return ;
	}
}

static void	child_heredoc(int *heredoc, char *delimiter, int *stdin)
{
	int	status;

	close(heredoc[0]);
	close(*stdin);
	signal(SIGINT, heredoc_ctrl_c);
	status = heredoc_read_loop(heredoc[1], delimiter);
	close(heredoc[1]);
	free(delimiter);
	exit(status);
}

static void	parent_error_heredoc(int *heredoc, int *stdin, t_data *d, pid_t pid)
{
	int	status;

	close(heredoc[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(heredoc[0]);
		close(*stdin);
		restore_terminal_settings();
		rl_on_new_line();
		rl_replace_line("", 0);
		signal(SIGINT, handler_ctrl_c);
		d->error_state = 130;
		return ;
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		close(heredoc[0]);
		close(*stdin);
		signal(SIGINT, handler_ctrl_c);
		d->error_state = 1;
		return ;
	}
	signal(SIGINT, handler_ctrl_c);
	dup2(heredoc[0], STDIN_FILENO);
	close(heredoc[0]);
	d->stdin_back = *stdin;
}

void	heredoc(t_data *d, int *pos, int i)
{
	int		heredoc[2];
	int		stdin;
	pid_t	pid;
	char	*delimiter;

	delimiter = ft_strdup(d->cmd[*pos].arguments[i].file);
	pid = -1;
	heredoc_error_handler(heredoc, &stdin);
	pid = heredoc_pid_create(heredoc, &stdin);
	if (pid == 0)
		child_heredoc(heredoc, delimiter, &stdin);
	else
	{
		parent_error_heredoc(heredoc, &stdin, d, pid);
		free(delimiter);
	}
}
