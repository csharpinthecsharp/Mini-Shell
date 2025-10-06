/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:59:55 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/07 00:44:33 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_command(char **argv)
{
    int len = ft_strlen(argv[0]);
    if (ft_strncmp(argv[0], "pwd", len) == 0)
        return (CUSTOM);
    else if (ft_strncmp(argv[0], "exit", len) == 0)
        return (STATEFUL);
    else if (ft_strncmp(argv[0], "echo", len) == 0)
        return (CUSTOM);
    else if (ft_strncmp(argv[0], "cd", len) == 0)
        return (STATEFUL);
    else if (ft_strncmp(argv[0], "export", len) == 0)
        return (STATEFUL);
    return (BUILT_IN);
}

int is_valid_bin(char *str)
{
    char *bin = ft_strdup(ft_strjoin("/bin/", str));
    int fd = open(bin, O_RDONLY);
    if (fd < 0)
        return (FAILED);
    close(fd);
    free(bin);
    return (SUCCESS);
}

size_t count_cmds(char ***cmds)
{
    size_t i = 0;
    while (cmds[i])
        i++;
    return (i - 1);
}

void close_pipe(int **var_pipe, int N_pipe, int state)
{
    int i = 0; 
    if (state == 1)
    {
        while (i < N_pipe)
        {
            close(var_pipe[i][0]);
            close(var_pipe[i][1]);
            i++;
        }
    }
    else
    {
        i = 0;
        while (i < N_pipe)
        {
            close(var_pipe[i][0]);
            close(var_pipe[i][1]);
            free(var_pipe[i]);
            i++;
        }
        free(var_pipe);
    }
}
