/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:59:55 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/21 16:00:41 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_output_ofeach(t_cmd *cmd, t_data *d)
{
    //for (int j = 0; d->output_file[index][j]; j++)
      //  printf("OUTPUTFILE: %s\n", d->output_file[index][j]);
    int i = 0;
    while (i < cmd->nb_redir)
    {
        int type = cmd->arguments[i].state_redir;
        char *file = cmd->arguments[i].file;
        if (file == NULL)
        {
            i += 1;   
            continue;
        }
        char *dir = get_directory(file);
        if ((type == RIGHT || type == RIGHT_RIGHT) && file)
        {
            if (!dir || access(dir, F_OK) != 0)
            {
                if (i == cmd->nb_redir)
                {
                    return FAILED;
                }
                else if (isatty(STDIN_FILENO))
                    print_error("No such file or directory", file); 
                else if (d->error_state == 0 && !isatty(STDIN_FILENO))
                {
                    print_error("No such file or directory", file); 
                    d->error_state = 1;
                }           
            }
            if (access(file, F_OK) == 0 && access(file, W_OK) != 0) 
            {
                if (errno == EACCES) 
                {
                    if (i == cmd->nb_redir)
                    {
                        return FAILED;
                    }
                    else if (isatty(STDIN_FILENO))
                        print_error("Permission denied", file); 
                    else if (d->error_state == 0 && !isatty(STDIN_FILENO))
                    {
                        print_error("Permission denied", file); 
                        d->error_state = 1;
                    }          
                }
            }
            free(dir); 
        }
        if ((type == LEFT) && file) 
        {
            if (access(file, F_OK) != 0) 
            {
                if (i == cmd->nb_redir)
                {
                    return FAILED;
                }
                else if (isatty(STDIN_FILENO))
                    print_error("No such file or directory", file); 
                else if (d->error_state == 0 && !isatty(STDIN_FILENO))
                {
                    print_error("No such file or directory", file); 
                    d->error_state = 1;
                }           
            }
            if (access(file, R_OK) != 0) 
            {
                if (errno == EACCES)
                {
                    if (i == cmd->nb_redir)
                    {
                        return FAILED;
                    }
                    else if (isatty(STDIN_FILENO))
                        print_error("Permission denied", file); 
                    else if (d->error_state == 0 && !isatty(STDIN_FILENO))
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

    // First pass: count only non-redirection args
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


int put_cmdstate(int type, int *is_stateful, t_cmd *cmd, t_data *d)
{
    int i = 0;
    while (1)
    {
        if (cmd[i].arg[0][0] == '$' && cmd[i].arg[0][1])
        {
            char *env = ft_get_env(d, cmd[i].arg[0]);
            if (!env)
            {
                int j = 0;
                while (j <= i)
                {
                    free(cmd[j].arg);
                    cmd[j].arg = NULL;
                    j++;
                }

                int k = 0;
                while (cmd[j].arg)
                {
                    cmd[k].arg = cmd[j].arg;
                    cmd[j].arg = NULL;
                    k++;
                    j++;
                }
                cmd[k].arg = NULL;

                if (!cmd[0].arg)
                    return FAILED;
                type = check_command(cmd[i].arg, d);
                i = 0;
                continue;
            }
        }
        else
            break;
        i++;
    }

    if (!cmd[i].arg)
    {
        if (d->nb_cmd)
            d->nb_cmd -= 1;
    }
   
    if (type == CUSTOM)
    {
        cmd->state_cmd = CUSTOM;
    }
    else if (type == ALONE_REDIR)
    {
        cmd->state_cmd = ALONE_REDIR;
    }
    else if (type == STATEFUL)
    {
        *is_stateful = 1;
        if (d->nb_cmd == 1)
        {
            run_custom_cmd(cmd[i].arg, d);
        }
        else
        {
            d->exit_status = 1;
            return FAILED;
        }
    }
    else if (type == BIN)
    {
        char *tmp = ft_strdup(cmd->arg[0]);
        if (do_cmd_exist(tmp, d) == SUCCESS)
        {
            cmd->state_cmd = BIN;
            free(tmp);
        }
        else
        {
            if (ft_strchr(tmp, '/') == NULL)
            {
                d->exit_status = 127;
                print_error("command not found", tmp);
                return FAILED;
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
                return FAILED;
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
                return FAILED;
            }

            // If file exists and is not a directory, but still not executable
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
                return FAILED;
            }
        }
    }
    return SUCCESS;
}

static bool check_alone_redir(char **argv)
{
    int i = 0;
    if (argv[i] + 1)
        return (true);
    return (false);
}

static bool is_alone_redir(char **argv, t_data *d)
{
    (void)d;
    if (ft_strncmp(argv[0], ">", 2) == 0
        && check_alone_redir(argv) == true)
    {
        d->curr_alone_r = ALONE_R;
        return (true);
    }
    else if (ft_strncmp(argv[0], ">>", 3) == 0
        && check_alone_redir(argv) == true)
    {
        d->curr_alone_r = ALONE_RR;
        return (true);
    }
    else if (ft_strncmp(argv[0], "<", 2) == 0
        && check_alone_redir(argv) == true)
    {
        d->curr_alone_r = ALONE_L;
        return (true);
    }
    else if (ft_strncmp(argv[0], "<<", 3) == 0
        && check_alone_redir(argv) == true)
    {
        d->curr_alone_r = ALONE_LL;
        return (true);
    }
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

int is_empty(t_data *d, int cmd_index, int arg_index)
{
    // If this argument slot was a redirection-only placeholder
    if (d->cmd[cmd_index].nb_redir > 0 &&
        d->cmd[cmd_index].arguments &&
        d->cmd[cmd_index].arguments[arg_index].state_redir == ALONE_REDIR)
    {
        return SUCCESS;
    }

    // If there is no actual command/argument at this index
    if (d->cmd[cmd_index].arg == NULL ||
        d->cmd[cmd_index].arg[arg_index] == NULL)
    {
        d->exit_status = 127;
        print_error("command not found ", "!");
        return FAILED;
    }

    return SUCCESS;
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