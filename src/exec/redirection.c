/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 13:41:22 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_command(char **argv)
{
    int len = ft_strlen(argv[0]);
    if (ft_strncmp(argv[0], "pwd", len) == 0)
        return (FAILED);
    else if (ft_strncmp(argv[0], "exit", len) == 0)
        return (FAILED);
    else if (ft_strncmp(argv[0], "echo", len) == 0)
        return (FAILED);
    else if (ft_strncmp(argv[0], "cd", len) == 0)
        return (FAILED);
    else if (ft_strncmp(argv[0], "export", len) == 0)
        return (FAILED);
    return (SUCCESS);
}

static int is_valid_bin(char *str)
{
    char *bin = ft_strdup(ft_strjoin("/bin/", str));
    int fd = open(bin, O_RDONLY);
    if (fd < 0)
        return (FAILED);
    return (SUCCESS);
}

static size_t count_cmds(t_data *d)
{
    d->cmd_count = 0;
    while (d->commands[d->cmd_count])
        d->cmd_count++;
    return (d->cmd_count);
}

int select_type(t_data *d)
{
    count_cmds(d);
    int i = 0;
    while (i <= d->cmd_count)
    {
        if (check_command(d->commands[i]) == FAILED)
        {
            if (run_custom_cmd(d) == FAILED)
                return (FAILED);
        }
        else if (check_command(d->commands[i]) == SUCCESS)
        {
            if (is_valid_bin(d->commands[i][0]) == SUCCESS)
            {
                if (run_build_cmd(d, d->envp) == FAILED)
                    return (FAILED);
            }
            else
                print_error("command not found", d->commands[i][0]);
        }
    }
    return (SUCCESS);
}