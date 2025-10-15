/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:19:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 15:44:04 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int start_point_parsing(t_data *d)
{
    if (d->input == NULL)
        return (FAILED);

    if (global_check(d) == 1)
        return (FAILED);

    d->input_splitted = split(d);
    if (d->input_splitted == NULL)
        return (FAILED);

    d->commands = split_commands(d->input_splitted);
    if (d->commands == NULL)
        return (FAILED);

    /* DEBUG ->
    for (int i = 0; d->commands[i]; i++)
    {
        printf("COMMAND [%d]:\n", i);
        for (int j = 0; d->commands[i][j]; j++)
            printf("[ARG OF CMD]: %s\n", d->commands[i][j]);
    }
    */
    if (start_execution(d) == FAILED)
        return (FAILED);
    return (SUCCESS);
}
