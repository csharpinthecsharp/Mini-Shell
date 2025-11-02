/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:22:20 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/01 17:41:33 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_heredocs(t_data *d, int *pos)
{
	int	i;
	int	last_heredoc;

	i = 0;
	last_heredoc = -1;
	while (i < d->cmd[*pos].nb_redir)
	{
		if (d->cmd[*pos].arguments[i].state_redir == LEFT_LEFT)
			last_heredoc = i;
		i++;
	}
	i = 0;
	while (i < d->cmd[*pos].nb_redir)
	{
		if (d->cmd[*pos].arguments[i].state_redir == LEFT_LEFT)
			heredoc(d, pos, i, (i == last_heredoc));
		i++;
	}
}

void	handle_bin(t_cmd *cmd, t_data *d)
{
	char	**paths;

	if (!cmd->arg[0])
		return ;
	if (ft_strchr(cmd->arg[0], '/'))
	{
		execve(cmd->arg[0], cmd->arg, d->envp);
		execve_error(cmd->arg[0]);
		return ;
	}
	paths = ft_split(ft_get_env(d, "PATH"), ':');
	if (!paths)
		return ;
	exec_with_path(paths, cmd, d);
	execve_error(cmd->arg[0]);
	free_split(paths);
}


void	handle_redirections(t_data *d, int *pos, int *fd_out, int *fd_in)
{
	int	i;

	i = 0;
	while (i < d->cmd[*pos].nb_redir)
	{
		if (d->cmd[*pos].arguments[i].state_redir == RIGHT)
			redirect_right(d, pos, *fd_out, i);
		else if (d->cmd[*pos].arguments[i].state_redir == RIGHT_RIGHT)
			redirect_right_right(d, pos, *fd_out, i);
		else if (d->cmd[*pos].arguments[i].state_redir == LEFT)
			redirect_left(d, pos, *fd_in, i);
		i++;
	}
}

void	handle_pipe(int **pipe, int *pos, int n_pipe)
{
	if (n_pipe > 0)
	{
		if (*pos > 0)
			dup2(pipe[*pos - 1][0], STDIN_FILENO);
		if (*pos < n_pipe)
			dup2(pipe[*pos][1], STDOUT_FILENO);
		close_pipe(pipe, n_pipe, 1);
	}
}

void	handle_child_status(t_data *d, pid_t wpid, int status, pid_t last_pid)
{
	if (wpid == last_pid)
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
		{
			print_error("Broken pipe", "!");
			d->exit_status = 1;
		}
		else if (WIFEXITED(status))
			d->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			d->exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGINT)
				write(STDOUT_FILENO, "\n", 1);
		}
	}
}
