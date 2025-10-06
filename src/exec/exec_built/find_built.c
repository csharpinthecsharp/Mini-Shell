/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:07:31 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 16:27:29 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int run_custom_cmd(char **argv, t_data *d)
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    int count = 0;

    while (argv[count])
        count++;
    if (ft_strncmp(argv[0], "pwd", 3) == 0)
    {
        if (handle_pwd(argv[0], count, d->path) == 1)
            return (1);
    }
    else if (ft_strncmp(argv[0], "exit", 4) == 0)
    {
        if (handle_exit(argv, count) == 1)
        {
            d->exit_status = 1;
            return (1);
        }
        else
            d->exit_status = 0;
    }
    else if (ft_strncmp(argv[0], "echo", 4) == 0)
    {
        if (handle_echo(argv, count) == 1)
        {
            d->exit_status = 1;
            return (1);
        }
        else
            d->exit_status = 0;
    }
    else if (ft_strncmp(argv[0], "cd", 2) == 0)
    {
        if (handle_cd(argv, count, d) == 1)
        {
            d->exit_status = 1;
            return (1);
        }
        else
            d->exit_status = 0;
    }
    else if (ft_strncmp(argv[0], "export", 6) == 0)
    {
        if (handle_export(argv, count, d) == 1)
        {
            d->exit_status = 1;
            return (1);
        }
        else
            d->exit_status = 0;
    }
    return (0);
}
