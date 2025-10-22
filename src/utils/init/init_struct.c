/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:35:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/23 00:29:58 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void update_data(t_data *d)
{
    free_beforenewline(d);

    d->curr_alone_r = 0;
    d->error_state = 0;
    d->input_splitted = NULL;
    d->new_path = NULL;
    d->stdin_back = -1;
    d->nb_cmd = 0;
    d->cmd = NULL;
}

void init_data(t_data *d)
{
    d->nb_cmd = 0;
    d->cmd = NULL;

    d->fd_in = -1;
    d->fd_out = -1;
    d->stdin_back = -1;

    d->input = NULL;
    d->input_splitted = NULL;
    d->path = NULL;
    d->new_path = NULL;

    d->error_state = 0;
    d->curr_alone_r = 0;
    d->exit_status = 0;

    d->envp = NULL;
    d->SHLVL = 1;
    d->last_fork_pid = -1;
}

