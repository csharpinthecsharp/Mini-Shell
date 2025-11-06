/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:55:32 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/06 15:37:41 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	start_execution(t_data *d)
{
	int		**pipe;
	int		pos;
	pid_t	last_pid;
	int		pipe_len;

	pos = 0;
	pipe_len = d->nb_cmd - 1;
	pipe = malloc(sizeof(int *) * pipe_len);
	if (!pipe || pipe_init(pipe_len, pipe) == FAILED)
	{
		close_pipe(pipe, pipe_len, 0);
		exit(FAILED);
	}
	while (pos < d->nb_cmd)
	{
		d->error_state = 0;
		execute_command_by_type(pipe, d, pipe_len, &pos);
		last_pid = d->last_fork_pid;
		pos++;
	}
	close_pipe(pipe, pipe_len, 0);
	wait_for_children(d, last_pid);
	restore_stdin(d);
}
