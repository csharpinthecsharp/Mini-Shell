/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:41:34 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 14:08:40 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void free_all(t_data *d, char *buffer)
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
    free(buffer);
}
