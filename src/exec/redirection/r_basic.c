/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_basic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:49:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 14:00:40 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	redirect_right(t_data *d, int *pos, int fd_out, int i)
{
	fd_out = open(d->cmd[*pos].arguments[i].file, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (fd_out < 0)
		exit(1);
	else
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	redirect_right_right(t_data *d, int *pos, int fd_out, int i)
{
	fd_out = open(d->cmd[*pos].arguments[i].file, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (fd_out < 0)
		exit(1);
	else
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	redirect_left(t_data *d, int *pos, int fd_in, int i)
{
	fd_in = open(d->cmd[*pos].arguments[i].file, O_RDONLY);
	if (fd_in < 0)
		exit(1);
	else
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}
