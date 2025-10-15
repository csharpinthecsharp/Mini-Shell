/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:59:55 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 16:25:06 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **fix_redir_arg(t_data *d, char **argv, int redir_type, int index)
{
    (void)redir_type;
    int i = 0;
    int j = 0;
    char **dup = malloc(sizeof(char *) * 256); 
    if (!dup)
    {
        perror("malloc failed");
        return NULL;
    }

    while (argv[i])
    {
        if ((ft_strncmp(argv[i], ">>", 2) == 0) ||
            (ft_strncmp(argv[i], "<<", 2) == 0) ||
            (ft_strncmp(argv[i], ">", 1) == 0) ||
            (ft_strncmp(argv[i], "<", 1) == 0))
        {
            if (argv[i + 1])
                (*d).output_file[index] = strdup(argv[i + 1]);
            i += 2;
            continue;
        }
        dup[j++] = ft_strdup(argv[i]);
        i++;
    }

    dup[j] = NULL;

    if (j == 0)
    {
        dup[0] = NULL;
        return (dup);
    }
    return (dup);
}

int put_cmdstate(int type, int *pos, int *is_stateful, t_data *d)
{
    if (type == CUSTOM)
        (*d).cmd_state[*pos] = CUSTOM;
    else if (type == STATEFUL)
    {
        *is_stateful = 1;
        if (d->cmd_count == 0)
            run_custom_cmd(d->commands[*pos], d);
        else
        {
            d->exit_status = 1;
            return (FAILED);
        }
    }
    else if (type == BIN)
    {
        if (is_valid_bin(d->commands[*pos][0]) == SUCCESS)
            (*d).cmd_state[*pos] = BIN;
        else
        {
            print_error("command not found", d->commands[*pos][0]);
            d->exit_status = 127;
            return (FAILED);
        } 
    }
    return (SUCCESS);
}
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
    else
        return (BIN);
}

int is_empty(int i, t_data *d)
{
    if (!d->commands[i] || !d->commands[i][0])
    {
        d->exit_status = 127;
        print_error("command not found", "!");
        return (FAILED);
    }
    return (SUCCESS);
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

int count_cmds(char ***cmds)
{
    int i = 0;
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
