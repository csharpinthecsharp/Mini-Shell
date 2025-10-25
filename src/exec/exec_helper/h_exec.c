/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:48:56 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 14:48:42 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	wait_for_children(t_data *d, pid_t last_pid)
{
	int		status;
	pid_t	wpid;

	wpid = wait(&status);
	while (wpid > 0)
	{
		handle_child_status(d, wpid, status, last_pid);
		wpid = wait(&status);
	}
}

void	restore_stdin(t_data *d)
{
	if (d->stdin_back != -1)
	{
		dup2(d->stdin_back, STDIN_FILENO);
		close(d->stdin_back);
		d->stdin_back = -1;
	}
}

void	close_pipe(int **var_pipe, int N_pipe, int state)
{
	int	i;

	i = 0;
	while (i < N_pipe)
	{
		close(var_pipe[i][0]);
		close(var_pipe[i][1]);
		if (state != 1)
			free(var_pipe[i]);
		i++;
	}
	if (state != 1)
		free(var_pipe);
}

int	pipe_init(int N_pipe, int **var_pipe)
{
	int	i;

	i = 0;
	while (i < N_pipe)
	{
		var_pipe[i] = malloc(sizeof(int) * 2);
		if (!var_pipe[i])
			return (FAILED);
		if (pipe(var_pipe[i]) == -1)
			return (FAILED);
		i++;
	}
	return (SUCCESS);
}
