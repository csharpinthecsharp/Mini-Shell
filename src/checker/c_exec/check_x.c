/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 01:07:11 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/24 14:00:39 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool check_alone_redir(char **argv)
{
    int i = 0;
    if (argv[i] + 1)
        return (true);
    return (false);
}

int check_command(char **argv, t_data *d)
{
    (void)d;
    bool res;
    
    res = is_alone_redir(argv, d);
    if (res == true)
        return (ALONE_REDIR);
    else
        d->curr_alone_r = 0;
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
        return (STATEFUL);
    else if (ft_strncmp(argv[0], "env", len) == 0)
        return (CUSTOM);
    else
        return (BIN);
}

int check_non_bin(t_cmd *cmd, int type, int *is_stateful, t_data *d)
{
    if (type == CUSTOM)
        cmd->state_cmd = CUSTOM;
    else if (type == ALONE_REDIR)
        cmd->state_cmd = ALONE_REDIR;
    else if (type == STATEFUL)
    {
        *is_stateful = 1;
        if (d->nb_cmd == 1)
            run_custom_cmd(&cmd->arg[0], d);
        else
        {
            d->exit_status = 1;
            return (FAILED);
        }
    }
    return (SUCCESS);
}

static void check_status_error(t_data *d, char *file, char *error_s)
{
    if (isatty(STDIN_FILENO))
        print_error(error_s, file); 
    else if (d->error_state == 0 && !isatty(STDIN_FILENO))
    {
        print_error(error_s, file); 
        d->error_state = 1;
    }  
}

static int check_dir_left(t_cmd *cmd, t_data *d, char *file, int type, int i)
{
    if ((type == LEFT) && file) 
    {
        if (access(file, F_OK) != 0) 
        {
            if (i == cmd->nb_redir)
            {
                return (FAILED);
            }   
            else
                check_status_error(d, file, "No such file or directory");
        }
        if (access(file, R_OK) != 0) 
        {
            if (errno == EACCES)
            {
                if (i == cmd->nb_redir)
                {
                    return FAILED;
                }
                else
                    check_status_error(d, file, "Permission denied");           
            }
        }
    }
    return (SUCCESS);
}

static int check_dir_right(t_cmd *cmd, t_data *d, char *dir, char *file, int type, int i)
{
    if ((type == RIGHT || type == RIGHT_RIGHT) && file)
    {
        if (!dir || access(dir, F_OK) != 0)
        {
            if (i == cmd->nb_redir)
            {
                return FAILED;
            }
            else
                check_status_error(d, file, "No such file or directory");       
        }
        if (access(file, F_OK) == 0 && access(file, W_OK) != 0) 
        {
            if (errno == EACCES) 
            {
                if (i == cmd->nb_redir)
                {
                    return (FAILED);
                }
                else
                    check_status_error(d, file, "Permission denied");
            }
        }
    }
    return (SUCCESS);
}

int check_output_ofeach(t_cmd *cmd, t_data *d)
{
    int i = 0;
    while (i < cmd->nb_redir)
    {
        if (cmd->arguments[i].file == NULL)
        {
            i += 1;   
            continue;
        }
        char *dir = get_directory(cmd->arguments[i].file);
        if (!dir)
            return (FAILED);
        if (check_dir_right(cmd, d, dir, cmd->arguments[i].file, cmd->arguments[i].state_redir, i) == FAILED)
        {
            free(dir);
            return (FAILED);
        }
        else if (check_dir_left(cmd, d, cmd->arguments[i].file, cmd->arguments[i].state_redir, i) == FAILED)
        {
            free(dir); 
            return (FAILED);
        }
        free(dir);
        i++;
    }
    return (SUCCESS);
}
