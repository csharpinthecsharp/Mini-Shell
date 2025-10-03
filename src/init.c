/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:35:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/03 02:55:07 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int locate_init(t_data *d)
{
    locate(d->input, QUOTE, d->s_quote);
    locate(d->input, BIG_QUOTE, d->s_big_quote);
    locate(d->input, PIPE, d->s_pipe);
    locate(d->input, ENV_VAR, d->s_env_var);
    return (0);
}