/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:35:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/27 20:07:55 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	init_data(t_data *d)
{
	d->nb_cmd = 0;
	d->cmd = NULL;
	d->fd_in = -1;
	d->fd_out = -1;
	d->stdin_back = -1;
	d->input = NULL;
	d->path = NULL;
	d->new_path = NULL;
	d->error_state = 0;
	d->curr_alone_r = 0;
	d->exit_status = 0;
	d->envp = NULL;
	d->last_fork_pid = -1;
	d->defer_errors = 0;
	d->errors = NULL;
}
