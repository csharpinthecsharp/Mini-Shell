/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:12:13 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/16 00:05:00 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void alloc_start_execution(t_data *d)
{
    d->cmd_count = count_cmds(d->commands);
    alloc_cmd_state(d);
    alloc_redir_state(d);
    alloc_output_file(d);
}

void alloc_cmd_state(t_data *d)
{
    d->cmd_state = malloc(sizeof(int) * d->cmd_count + 1);
    if (!d->cmd_state)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
}

void alloc_redir_state(t_data *d)
{
    d->redirection_state = malloc(sizeof(int) * d->cmd_count + 1);
    if (!d->redirection_state)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
}

void alloc_output_file(t_data *d)
{
    d->output_file = malloc(sizeof(char *) * d->cmd_count + 1);
    if (!d->output_file)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
}   