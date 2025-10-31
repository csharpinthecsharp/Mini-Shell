/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:16:18 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/31 20:51:16 by astrelci         ###   ########.fr       */
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
	char	*res;

	res = NULL;
	close(heredoc[0]);
	close(*stdin);
	signal(SIGINT, heredoc_ctrl_c);
	while (1)
	{
		res = readline("> ");
		if (!res)
		{
			print_error("here-document delimited by end-of-file", "warning");
			break ;
		}
		if (strcmp(res, delimiter) == 0)
		{
			free(res);
			break ;
		}
		ft_putstr_fd(res, heredoc[1]);
		ft_putstr_fd("\n", heredoc[1]);
		free(res);
	}
	close(heredoc[1]);
	exit(0);
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
		rl_on_new_line();
		rl_replace_line("", 0);
		signal(SIGINT, handler_ctrl_c);
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
		parent_error_heredoc(heredoc, &stdin, d, pid);
}
