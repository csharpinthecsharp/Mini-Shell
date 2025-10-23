/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_pre_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:47:20 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/23 17:38:20 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char *get_directory(const char *path)
{
    int len = ft_strlen(path);
    int i = len - 1;

    while (i >= 0 && path[i] != '/')
        i--;

        
    if (i < 0)
        return strdup(".");

    char *dir = malloc(i + 1);
    if (!dir)
        return NULL;

    strncpy(dir, path, i);
    dir[i] = '\0';
    return dir;
}

char **fix_redir_arg(t_cmd *cmd)
{
    int i = 0;
    int arg_count = 0;

    while (i < cmd->nb_arg)
    {
        if ((!ft_strncmp(cmd->arg[i], ">>", 3) ||
             !ft_strncmp(cmd->arg[i], "<<", 3) ||
             !ft_strncmp(cmd->arg[i], ">", 2)  ||
             !ft_strncmp(cmd->arg[i], "<", 2)) &&
            cmd->arg[i + 1]) // make sure filename exists
        {
            i += 2; // skip operator + filename
        }
        else {
            arg_count++;
            i++;
        }
    }

    char **dup = malloc(sizeof(char *) * (arg_count + 1));
    if (!dup)
        return NULL;

    // Second pass: copy only non-redirection args
    i = 0;
    int arg_j = 0;
    while (i < cmd->nb_arg)
    {
        if ((!ft_strncmp(cmd->arg[i], ">>", 3) ||
             !ft_strncmp(cmd->arg[i], "<<", 3) ||
             !ft_strncmp(cmd->arg[i], ">", 2)  ||
             !ft_strncmp(cmd->arg[i], "<", 2)) &&
            cmd->arg[i + 1])
        {
            i += 2;
            continue;
        }
        dup[arg_j++] = ft_strdup(cmd->arg[i]);
        i++;
    }
    dup[arg_j] = NULL;

    // update nb_arg to new count
    cmd->nb_arg = arg_count;

    return dup;
}

static int error_h(t_data *d, char *tmp)
{
    if (ft_strchr(tmp, '/') == NULL)
    {
        d->exit_status = 127;
        print_error("command not found", tmp);
        return (FAILED);
    }
    
    struct stat st;
    if (stat(tmp, &st) == -1)
    {
        if (errno == ENOENT && ft_strchr(tmp, '/') != NULL)
        {
            d->exit_status = 127;
            print_error("No such file or directory", tmp);
        }
        else if (errno == EACCES)
        {
            d->exit_status = 126;
            print_error("Permission denied", tmp);
        }
        else
        {
            d->exit_status = 127;
            print_error("command not found", tmp);
        }
        return (FAILED);
    }

    if (S_ISDIR(st.st_mode))
    {
        if (ft_strchr(tmp, '/') != NULL)
        {
            d->exit_status = 126;
            print_error("Is a directory", tmp);
        }
        else
        {
            d->exit_status = 127;
            print_error("command not found", tmp);
        }
        return (FAILED);
    }

    if (access(tmp, X_OK) != 0)
    {
        if (errno == EACCES)
        {
            d->exit_status = 126;
            print_error("Permission denied", tmp);
        }
        else
        {
            d->exit_status = 127;
            print_error("command not found", tmp);
        }
        return (FAILED);
    }
    return (SUCCESS);
}

int put_cmdstate(int type, int *is_stateful, t_cmd *cmd, t_data *d)
{
    if (check_non_bin(cmd, type, is_stateful, d) == FAILED)
        return (FAILED);
    else if (type == BIN)
    {
        char *tmp = ft_strdup(cmd->arg[0]);
        if (is_available(tmp, d) == SUCCESS)
        {
            cmd->state_cmd = BIN;
            free(tmp);
        }
        else
        {
            if (error_h(d, tmp) == FAILED)
            {
                free(tmp);
                return (FAILED);
            }
        }
    }
    return (SUCCESS);
}

