/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:35:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 00:13:03 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int update_data(t_data *d)
{
    d->input = NULL;
    d->input_splitted = NULL;
    d->path = NULL;
    d->commands = NULL;
    return (0);
}
