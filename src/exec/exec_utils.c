/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:59:55 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/18 22:40:18 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_output_ofeach(t_data *d, int index)
{
    //for (int j = 0; d->output_file[index][j]; j++)
      //  printf("OUTPUTFILE: %s\n", d->output_file[index][j]);
    int i = 0;
    while (i < d->N_redir[index]) 
    {
        int type = d->redirection_state[index][i];
        char *file = d->output_file[index][i];
        char *dir = get_directory(file);
        if ((type == RIGHT || type == RIGHT_RIGHT) && file)
        {
            if (!dir || access(dir, F_OK) != 0)
            {
                if (i == d->N_redir[index])
                    return FAILED;

                if (d->error_state == 0)
                {  
                    print_error("No such file or directory", file);   
                    d->error_state = 1;
                }
            }
            if (access(file, F_OK) == 0 && access(file, W_OK) != 0) 
            {
                if (errno == EACCES) 
                {
                    if (i == d->N_redir[index])
                        return FAILED;
                    if (d->error_state == 0)
                    {  
                        print_error("Permission denied", file);   
                        d->error_state = 1;
                    }
                }
            }
            free(dir); 
        }
        if ((type == LEFT || type == LEFT_LEFT) && file) 
        {
            if (access(file, F_OK) != 0) 
            {
                if (i == d->N_redir[index])
                    return FAILED;
                if (d->error_state == 0)
                {  
                    print_error("No such file or directory", file);   
                    d->error_state = 1;
                }
            }
            if (access(file, R_OK) != 0) 
            {
                if (errno == EACCES)
                {
                    if (i == d->N_redir[index])
                        return FAILED;
                    if (d->error_state == 0)
                    {  
                        print_error("Permission denied", file);   
                        d->error_state = 1;
                    }                
                }
            }
        }
        i++;
    }
    return (SUCCESS);
}


char *get_directory(const char *path)
{
    int len = strlen(path);
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

char **fix_redir_arg(t_data *d, char **argv, int index)
{
    (void)d;
    (void)index;
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
        if ((ft_strncmp(argv[i], ">>", 3) == 0) ||
            (ft_strncmp(argv[i], "<<", 3) == 0) ||
            (ft_strncmp(argv[i], ">", 2) == 0) ||
            (ft_strncmp(argv[i], "<", 2) == 0))
        {
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
    {
        d->cmd_state[*pos] = CUSTOM;
    }
    else if (type == STATEFUL)
    {
        *is_stateful = 1;
        if (d->cmd_count == 0)
        {
            run_custom_cmd(d->commands[*pos], d);
        }
        else
        {
            d->exit_status = 1;
            return FAILED;
        }
    }
    else if (type == BIN)
    {
        char *cmd = d->commands[*pos][0];

        if (do_cmd_exist(cmd, d) == SUCCESS)
        {
            d->cmd_state[*pos] = BIN;
        }
        else
        {
            if (ft_strchr(cmd, '/') == NULL)
            {
                d->exit_status = 127;
                print_error("command not found", cmd);
                return FAILED;
            }
            
            struct stat st;
            if (stat(cmd, &st) == -1)
            {
                if (errno == ENOENT && ft_strchr(cmd, '/') != NULL)
                {
                    d->exit_status = 127;
                    print_error("No such file or directory", cmd);
                }
                else if (errno == EACCES)
                {
                    d->exit_status = 126;
                    print_error("Permission denied", cmd);
                }
                else
                {
                    d->exit_status = 127;
                    print_error("command not found", cmd);
                }
                return FAILED;
            }

            if (S_ISDIR(st.st_mode))
            {
                if (ft_strchr(cmd, '/') != NULL)
                {
                    d->exit_status = 126;
                    print_error("Is a directory", cmd);
                }
                else
                {
                    d->exit_status = 127;
                    print_error("command not found", cmd);
                }
                return FAILED;
            }

            // If file exists and is not a directory, but still not executable
            if (access(cmd, X_OK) != 0)
            {
                if (errno == EACCES)
                {
                    d->exit_status = 126;
                    print_error("Permission denied", cmd);
                }
                else
                {
                    d->exit_status = 127;
                    print_error("command not found", cmd);
                }
                return FAILED;
            }

            // If none of the above, fallback
            d->exit_status = 127;
            print_error("command not found", cmd);
            return FAILED;
        }
    }
    return SUCCESS;
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
        return (STATEFUL);
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

int do_cmd_exist(char *str, t_data *d)
{
    char *res;
    if (ft_strncmp(str, "/bin/", 5) == 0)
        res = str;
    else
        res = ft_strjoin("/bin/", str);

    if (access(res, R_OK) != 0)
    {
        d->exit_status = 127;
        if (res != str)
            free(res);
        return (FAILED);
    }
    if (res != str)
        free(res);
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