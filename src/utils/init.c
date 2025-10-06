/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:35:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 19:55:22 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int update_data(t_data *d)
{
    d->input = NULL;
    d->input_splitted = NULL;
    d->path = NULL;
    d->commands = NULL;
    d->cmd_state = NULL;
    d->cmd_count = 0;
    return (0);
}

void free_all(t_data *d)
{
    if (d->cmd_state)
        free(d->cmd_state);

    if (d->commands) {
        for (int i = 0; d->commands[i]; i++) {
            for (int j = 0; d->commands[i][j]; j++)
                free(d->commands[i][j]);
            free(d->commands[i]);
        }
        free(d->commands);
    }

    if (d->input)
        free(d->input);

    if (d->input_splitted) {
        for (int i = 0; d->input_splitted[i]; i++)
            free(d->input_splitted[i]);
        free(d->input_splitted);
    }
    free(d->path);
}
