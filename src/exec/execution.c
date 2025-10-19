/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/20 00:11:01 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* ************************************************************************** */
/*                           TODO POUR 100% TESTEUR                           */
/*                                                                            */
/* - Boucles d’index :                                                        */
/*   -> Utiliser i < d->cmd_count (et pas <=)                                 */
/*   -> Dans run_non_stateful : pos < N_pipe + 1                              */
/*                                                                            */
/* - Redirections :                                                           */
/*   -> Vérifier et appliquer les redirections dans chaque enfant (pid == 0)  */
/*   -> Toujours traiter les entrées (<) avant les sorties (>, >>)            */
/*   -> Appliquer dup2 uniquement sur la DERNIÈRE redirection de chaque type  */
/*   -> Ouvrir les précédentes juste pour créer/vider le fichier              */
/*                                                                            */
/* - Erreurs :                                                                */
/*   -> Toujours afficher l’erreur (No such file / Permission denied)         */
/*   -> exit_status = 1 uniquement si :                                       */
/*        * c’est la dernière commande du pipeline                            */
/*        * et la redirection fautive est la dernière effective               */
/*   -> Ne pas créer de fichier de sortie si une redirection d’entrée échoue  */
/*                                                                            */
/* - check_output_ofeach :                                                    */
/*   -> Utiliser i == d->N_redir[index] - 1 (pas i == d->N_redir[index])      */
/*   -> Ne retourner FAILED que pour la dernière commande                     */
/*                                                                            */
/* - Divers :                                                                 */
/*   -> Supprimer ft_strdup(ft_strjoin(...)), utiliser seulement ft_strjoin   */
/*   -> Corriger if (d->N_redir > 0) -> if (d->N_redir[i] > 0)                */
/*   -> Messages d’erreur cohérents avec Bash (ENOENT, EACCES, etc.)          */
/*                                                                            */
/* Résumé :                                                                   */
/*   Respecter l’ordre et la logique de Bash :                                */
/*   - Entrées avant sorties                                                  */
/*   - Dernière redirection appliquée                                         */
/*   - Erreurs toujours affichées                                             */
/*   - Code de sortie correct uniquement si dernière commande                 */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int start_execution(t_data *d)
{
    int i = 0;
    int is_stateful;

    i = 0;
    is_stateful = 0;
    alloc_start_execution(d);
    int count = 0;
    d->N_redir = ft_calloc(64, sizeof(int));
    while ((i <= d->cmd_count))
    {
        int pos = 0;
        count += is_redirect(d->commands[i], d, &pos, i);
        i++;
    }
    d->N_redirfull = count;

    i = 0;
    while (i <= d->cmd_count)
    {
        if (is_empty(i, d, 0) == FAILED)
            return (FAILED);
        int type = check_command(d->commands[i], d);
        if (put_cmdstate(type, &i, &is_stateful, d) == FAILED)
                return (FAILED);

        if (d->N_redir > 0)
        {            
            d->commands[i] = fix_redir_arg(d, d->commands[i], i);
            if (is_empty(i, d, 0) == 1)
                return (FAILED);
        }
        i++;
    }
    if (is_stateful == 0)
        run_non_stateful(d, d->cmd_count);
    return (SUCCESS);
}

static void exec_alone_redir_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    int i = 0;
    while (d->redirection_state[*pos][i])
    {
        if (d->redirection_state[*pos][i] == LEFT_LEFT)
            heredoc(d, pos, i);
        i++;
    }
    
    i = 0;
    int fd_out = 0;
    int fd_in = 0;
    if (d->cmd_state[*pos] == ALONE_REDIR)
    {
        if (N_pipe > 0 || d->N_redir > 0)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                if (N_pipe > 0)
                {
                    if (*pos > 0)
                        dup2(var_pipe[*pos - 1][0], STDIN_FILENO);
                    if (*pos < N_pipe)
                        dup2(var_pipe[*pos][1], STDOUT_FILENO);

                    close_pipe(var_pipe, N_pipe, 1);
                }
                
                int i = 0;
                while (d->redirection_state[*pos][i])
                {
                    if (d->redirection_state[*pos][i] == RIGHT)
                        redirect_right(d, pos, fd_out, i);
                    else if (d->redirection_state[*pos][i] == RIGHT_RIGHT)
                        redirect_right_right(d, pos, fd_out, i);
                    else if (d->redirection_state[*pos][i] == LEFT)
                        redirect_left(d, pos, fd_in, i);
                    i++;
                } 
                exit(d->exit_status);
            }
            else if (pid > 0)
                d->last_fork_pid = pid;
        }
    }
}

static void exec_custom_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    int i = 0;
    while (d->redirection_state[*pos][i])
    {
        if (d->redirection_state[*pos][i] == LEFT_LEFT)
            heredoc(d, pos, i);
        i++;
    }
    
    i = 0;
    int fd_out = 0;
    int fd_in = 0;
    if (d->cmd_state[*pos] == CUSTOM)
    {
        if (N_pipe > 0 || d->N_redir > 0)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                if (N_pipe > 0)
                {
                    if (*pos > 0)
                        dup2(var_pipe[*pos - 1][0], STDIN_FILENO);
                    if (*pos < N_pipe)
                        dup2(var_pipe[*pos][1], STDOUT_FILENO);

                    close_pipe(var_pipe, N_pipe, 1);
                }
                
                int i = 0;
                while (d->redirection_state[*pos][i])
                {
                    if (d->redirection_state[*pos][i] == RIGHT)
                        redirect_right(d, pos, fd_out, i);
                    else if (d->redirection_state[*pos][i] == RIGHT_RIGHT)
                        redirect_right_right(d, pos, fd_out, i);
                    else if (d->redirection_state[*pos][i] == LEFT)
                        redirect_left(d, pos, fd_in, i);
                    i++;
                }
                    
                run_custom_cmd(d->commands[*pos], d);
                exit(d->exit_status);
            }
            else if (pid > 0)
                d->last_fork_pid = pid;
        }
        else
            run_custom_cmd(d->commands[*pos], d);
    }
}
static void execve_error(char *cmd)
{
    if (errno == ENOENT)
        print_error("Command or file not found", cmd);
    else if (errno == EACCES)
        print_error("Permission denied", cmd);
    else if (errno == ENOMEM)
        print_error("Not enough memory", cmd);
    else if (errno == EFAULT)
        print_error("Invalid pointer", cmd);
    else if (errno == EINVAL)
        print_error("Invalid argument", cmd);
    else if (errno == ENOTDIR)
        print_error("A path component is not a directory", cmd);
    else
        print_error("Execution failed", cmd);
}
static void exec_built_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    int i = 0;
    while (d->redirection_state[*pos][i])
    {
        if (d->redirection_state[*pos][i] == LEFT_LEFT)
            heredoc(d, pos, i);
        i++;
    }
    
    i = 0;
    int fd_out = 0;
    int fd_in = 0;
    pid_t pid = fork();
    if (pid == 0)
    {
        if (N_pipe > 0)
        {
            if ((*pos) > 0)
                dup2(var_pipe[(*pos) - 1][0], STDIN_FILENO);
            if ((*pos) < N_pipe)
                dup2(var_pipe[(*pos)][1], STDOUT_FILENO);
            close_pipe(var_pipe, N_pipe, 1);
        }
        
        int i = 0;
        while (d->redirection_state[*pos][i])
        {
            if (d->redirection_state[*pos][i] == RIGHT)
                redirect_right(d, pos, fd_out, i);
            else if (d->redirection_state[*pos][i] == RIGHT_RIGHT)
                redirect_right_right(d, pos, fd_out, i);
            else if (d->redirection_state[*pos][i] == LEFT)
                redirect_left(d, pos, fd_in, i);
            i++;
        }
        
        if (ft_strncmp(d->commands[*pos][0], "/bin/", 5) == 0)
        {
            execve(d->commands[*pos][0], d->commands[*pos], d->envp);
            execve_error(d->commands[*pos][0]);
        }
        else
        {
            char *tmp_cmd = ft_strdup(ft_strjoin("/bin/", d->commands[*pos][0]));
            execve(tmp_cmd, d->commands[*pos], d->envp);
            execve_error(tmp_cmd);
            free(tmp_cmd);
        }

        exit(127);
    }
    else if (pid > 0)
        d->last_fork_pid = pid;
}

void run_non_stateful(t_data *d, int N_pipe)
{
    int **var_pipe = malloc(sizeof(int *) * N_pipe);
    pid_t last_pid = -1;
    if (!var_pipe)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    alloc_error_pipe(N_pipe, var_pipe);
    int pos = 0;
    while (pos <= N_pipe)
    {
        if (check_output_ofeach(d, pos) == FAILED)
            exit(d->exit_status);
        if ((*d).cmd_state[pos] == CUSTOM)
            exec_custom_inpipe(var_pipe, d, N_pipe, &pos);
        else if ((*d).cmd_state[pos] == BIN)
            exec_built_inpipe(var_pipe, d, N_pipe, &pos);
        else if ((*d).cmd_state[pos] == ALONE_REDIR)
            exec_alone_redir_inpipe(var_pipe, d, N_pipe, &pos);
        last_pid = d->last_fork_pid;
        pos++;
    }
    close_pipe(var_pipe, N_pipe, 0);
    int status;
    pid_t wpid;
    pos = 0;
    while ((wpid = wait(&status)) > 0)
    {
        if (wpid == last_pid)
        {
            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
            {
                print_error("Broken pipe", "!");
                d->exit_status = 1;
            }
            if (WIFEXITED(status))
                d->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                d->exit_status = 128 + WTERMSIG(status);
        }
        pos++;
    }
    
    if (d->stdin_back != -1)
    {
        dup2(d->stdin_back, STDIN_FILENO);
        close(d->stdin_back);
        d->stdin_back = -1;
    }
}