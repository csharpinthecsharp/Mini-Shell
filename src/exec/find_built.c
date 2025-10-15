/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:07:31 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 02:35:50 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int run_custom_cmd(char **argv, t_data *d)
{
    int count = 0;
    while (argv[count])
        count++;
    
    if (ft_strncmp(argv[0], "pwd", 3) == 0)
    {
        d->exit_status = handle_pwd(argv[0], count, d->path);
    }
    else if (ft_strncmp(argv[0], "exit", 4) == 0)
    {
        d->exit_status = handle_exit(argv, count);
    }
    else if (ft_strncmp(argv[0], "echo", 4) == 0)
    {
        d->exit_status = handle_echo(argv, count);
    }
    else if (ft_strncmp(argv[0], "cd", 2) == 0)
    {
        d->exit_status = handle_cd(argv, count, d);
    }
    else if (ft_strncmp(argv[0], "export", 6) == 0)
    {
        d->exit_status = handle_export(argv, count, d);
    }
    else if (ft_strncmp(argv[0], "env", 3) == 0)
    {
        d->exit_status = handle_env(argv, count, d);
    }
    else if (ft_strncmp(argv[0], "unset", 5) == 0)
    {
        d->exit_status = handle_unset(argv, count, d);
    }
    else
    {
        print_error("builtin command not found", argv[0]);
        d->exit_status = 126;
    }
    return (0);
}