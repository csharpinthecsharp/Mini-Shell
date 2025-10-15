/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:59:55 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 02:32:47 by ltrillar         ###   ########.fr       */
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
    else if (ft_strncmp(argv[0], "unset", len) == 0)
        return (CUSTOM);
    else if (ft_strncmp(argv[0], "env", len) == 0)
        return (CUSTOM);
    return (BIN);
}

int is_valid_bin(char *str)
{
    int fd;
    if (ft_strncmp(str, "/bin/", 5) == 0)
        fd = open(str, O_RDONLY);
    else
    {
        char *bin = ft_strjoin("/bin/", str);
        fd = open(bin, O_RDONLY);
        free(bin);
    }
    if (fd < 0)
        return (FAILED);
    close(fd);
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
    while (i < N_pipe)
    {
        close(var_pipe[i][0]);
        close(var_pipe[i][1]);
        if (state != 1)
            free(var_pipe[i]);
        i++;
    }
    if (state != 1)
        free(var_pipe);
}
