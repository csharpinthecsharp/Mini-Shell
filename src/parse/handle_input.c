/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:19:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 13:15:50 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int filter_input(t_data *d)
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    if (d->input == NULL)
        return (FAILED);

    //validate token, if return success,
    // it mean that this not passed.
    if (global_check(d) == 1)
        return (SUCCESS);

    d->input_splitted = split(d);
    if (d->input_splitted == NULL)
        return (FAILED);

    d->commands = split_commands(d->input_splitted);
    if (d->commands == NULL)
        return (FAILED);

    if (select_type(d) == FAILED)
        return (FAILED);
    return (SUCCESS);
}
