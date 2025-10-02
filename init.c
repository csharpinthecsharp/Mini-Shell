/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:35:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/02 15:47:35 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int update_data(t_data *d)
{
    d->c_big_quote = 0;
    d->c_env_var = 0;
    d->c_pipe = 0;
    d->c_quote = 0;
    d->input = NULL;
    d->input_splitted = NULL;
    d->path = NULL;
    return (0);
}