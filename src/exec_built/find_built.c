/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:07:31 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 20:37:52 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int run_custom_cmd(t_data *d)
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    int count = 0;

    while (d->input_splitted[count])
        count++;
    if (ft_strncmp(d->input_splitted[0], "pwd", 3) == 0)
    {
        if (handle_pwd(d->input_splitted[0], count, d->path) == 1)
            return (1);
    }
    else if (ft_strncmp(d->input_splitted[0], "exit", 4) == 0)
    {
        if (handle_exit(d->input_splitted, count) == 1)
        {
            d->exit_status = 1;
            return (1);
        }
        else
            d->exit_status = 0;
    }
    else if (ft_strncmp(d->input_splitted[0], "echo", 4) == 0)
    {
        if (handle_echo(d->input_splitted, count) == 1)
        {
            d->exit_status = 1;
            return (1);
        }
        else
            d->exit_status = 0;
    }
    else if (ft_strncmp(d->input_splitted[0], "cd", 2) == 0)
    {
        if (handle_cd(d->input_splitted, count, d) == 1)
        {
            d->exit_status = 1;
            return (1);
        }
        else
            d->exit_status = 0;
    }
    else if (ft_strncmp(d->input_splitted[0], "export", 6) == 0)
    {
        if (handle_export(d->input_splitted, count, d) == 1)
        {
            d->exit_status = 1;
            return (1);
        }
        else
            d->exit_status = 0;
    }
    return (0);
}
