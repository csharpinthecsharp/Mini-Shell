/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:19:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/12 15:09:56 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int filter_input(t_data *d)
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    if (d->input == NULL)
    {
        return (FAILED);
    }
    d->input_splitted = split(d);
    if (d->input_splitted == NULL)
        return (FAILED);
    // Les commandes ne peuvent etre séparé que par des pipes dans le projet.
    // Ducoup d->commands return par exemple: cat src/main.c | grep return
    // -> commands[0] = cat src/main.c
    // -> commands[1] = grep return
    d->commands = split_commands(d->input_splitted);
    if (d->commands == NULL)
        return (FAILED);

    if (select_type(d) == FAILED)
        return (FAILED);
    return (SUCCESS);
}
