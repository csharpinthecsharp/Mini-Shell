/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:35:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/20 16:37:01 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	update_data(t_data *d)
{
	d->curr_alone_r = 0;
	d->error_state = 0;
	d->kill_heredoc = 0;
	d->in_heredoc = 0;
	d->input = NULL;
	d->input_splitted = NULL;
	d->path = NULL;
	d->commands = NULL;
	d->cmd_state = NULL;
	d->cmd_count = 0;
	d->N_redir = 0;
	d->new_path = NULL;
	d->stdin_back = -1;
}

void	init_data(t_data *d)
{
	d->curr_alone_r = 0;
	d->error_state = 0;
	d->N_redirfull = 0;
	d->kill_execution = 0;
	d->kill_heredoc = 0;
	d->exit_status = 0;
	d->input = NULL;
	d->input_splitted = NULL;
	d->path = NULL;
	d->commands = NULL;
	d->cmd_state = NULL;
	d->cmd_count = 0;
	d->N_redir = 0;
	d->new_path = NULL;
}
