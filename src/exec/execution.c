/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/10 00:39:34 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
 
int select_type(t_data *d)
{
    size_t i = 0;
    alloc_cmd_state(d);
    alloc_redir_state(d);
    
    i = 0;
    while (i <= d->cmd_count)
    {
        int type = check_command(d->commands[i]);
        int redir_type = is_redirect(d->commands[i]);
        
        if (redir_type > NOT_FOUND)
        {
            (*d).redirection_state[i] = redir_type;
            // Pour réorganiser la d->commands[i]
            // et store le name_file EXEMPLE:
            // ls > test.txt
            // fix_redir_arg() = ls
            // d->store_redir = test.txt
            d->commands[i] = fix_redir_arg(d, d->commands[i], redir_type, i);
        }
        else
            (*d).redirection_state[i] = 0;
            
        if (type == CUSTOM)
            (*d).cmd_state[i] = CUSTOM;
        else if (type == STATEFUL)
        {
            if (d->cmd_count == 0)
                run_custom_cmd(d->commands[i], d);
            else
                print_error("can't run in a pipe command", d->commands[i][0]);
        }
        else if (type == BUILT_IN)
        {
            if (is_valid_bin(d->commands[i][0]) == SUCCESS)
                (*d).cmd_state[i] = BUILT_IN;
            else
                print_error("command not found", d->commands[i][0]); 
        }
        i++;
    }
    run_pipe_cmd(d, pipe_count(d->input_splitted));
    return (SUCCESS);
}

static char *send_output(char **argv, int redir_state)
{
    int i = 0;
    if (redir_state == RIGHT)
    {
        while (argv[i] && argv[i][0] != '>')
            i++;
        while (argv[i] && argv[i + 1])
            return (ft_strdup(argv[i + 1]));
    }
    return (NULL);
}
// Redirection de la sortie standard avec dup2()
// Exemple : commande "ls > output.txt"
// Étapes :
// 1. Extraire le nom du fichier après '>'
// 2. Ouvrir le fichier en écriture avec open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)
// 3. Rediriger stdout avec dup2(fd_out, STDOUT_FILENO)
// 4. Exécuter la commande avec execvp()
// Pas besoin de read() ou write() manuels — dup2 gère la redirection automatiquement
char **fix_redir_arg(t_data *d, char **argv, int redir_type, int index)
{
    // TEMP MALLOC AHAHHH
    d->output_file = malloc(sizeof(char *) * BUFFER_SIZE);
    
    int i = 0;
    while (argv[i])
    {
        if (ft_strncmp(argv[i], ">", 1) == 0) 
            break;
        i++;
    }
        
    char **dup = malloc(sizeof(char *) * (i + 1));
    if (!dup)
    {
        perror("malloc failed");
        return (NULL);
    }
        
    int j = 0;
    while (j < i)
    {
        dup[j] = ft_strdup(argv[j]);
        j++;
    }
    // ls > test.txt
    // bah on envoi test.txt a d->output_file[i]
    if (redir_type == RIGHT)
        (*d).output_file[index] = send_output(argv, RIGHT);
    dup[i] = NULL;
    return (dup);
}

int is_redirect(char **argv)
{
    int i = 0;
    int count_left = 0;
    int count_right = 0;
    while (argv[i])
    {
        if (argv[i][0] == '>')
        {
            //*(tell_me_where) = i;
            count_right++;
        }
        else if (argv[i][0] == '<')
            count_left++;
        i++;
    }
    if (count_left + count_right == 0)
        return (NOT_FOUND);
    else if (count_left == 1 && count_right == 0)
        return (LEFT);
    else if (count_left == 2 && count_right == 0)
        return (LEFT_LEFT);
    else if (count_left == 0 && count_right == 1)
        return (RIGHT);
    else if (count_left == 0 && count_right == 2)
        return (RIGHT_RIGHT);
    else
        return (ERROR);
}


static void exec_custom_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    int fd_out;
    if ((*d).cmd_state[*pos] == CUSTOM)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            if (d->redirection_state[*pos] == RIGHT)
            {
                fd_out = open(d->output_file[*pos], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_out < 0)
                    print_error("open failed", "oui");
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }
            if ((*pos) > 0)
                dup2(var_pipe[(*pos) - 1][0], STDIN_FILENO);
            else if ((*pos) < N_pipe)
                dup2(var_pipe[(*pos)][1], STDOUT_FILENO);
            close_pipe(var_pipe, N_pipe, 1);
            run_custom_cmd(d->commands[(*pos)], d);
            exit(EXIT_SUCCESS);
        }
     }
}

/*
 * Gestion de la redirection de sortie (>):
 *
 * - O_TRUNC : utilisé avec open() pour tronquer le fichier cible, c’est-à-dire écraser son contenu s’il existe déjà.
 * - 0644   : permissions classiques pour les fichiers créés (lecture/écriture pour le propriétaire, lecture seule pour les autres).
 *
 * Fonctions à implémenter :
 * - is_output_redirection() :
 *     Vérifie si la commande contient une redirection de sortie ('>').
 *     Exemple : "ls > out.txt" → retourne true.
 *
 * - get_output_filename() :
 *     Extrait le nom du fichier vers lequel rediriger la sortie.
 *     Exemple : "ls > out.txt" → retourne "out.txt".
 *
 * Ces fonctions permettent d’ouvrir le bon fichier avec open(),
 * puis de rediriger STDOUT vers ce fichier avec dup2(fd, STDOUT_FILENO).
 */

static void exec_built_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    pid_t pid = fork();
    int fd_out;
    if (pid == 0)
    {
        if (d->redirection_state[*pos] == RIGHT)
        {
            fd_out = open(d->output_file[*pos], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0)
                print_error("open failed", "oui");
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        if ((*pos) > 0)
            dup2(var_pipe[*pos - 1][0], STDIN_FILENO);
        else if ((*pos) < N_pipe)
            dup2(var_pipe[*pos][1], STDOUT_FILENO);
        close_pipe(var_pipe, N_pipe, 1);
        char *tmp_cmd = ft_strdup(ft_strjoin("/bin/", d->commands[*pos][0]));
        execve(tmp_cmd, d->commands[*pos], d->envp);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
}

void run_pipe_cmd(t_data *d, int N_pipe)
{
    int **var_pipe = malloc(sizeof(int *) * N_pipe);
    if (!var_pipe)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    alloc_error_pipe(N_pipe, var_pipe);
    int pos = 0;
    while (pos <= N_pipe)
    {
        if ((*d).cmd_state[pos] == CUSTOM)
            exec_custom_inpipe(var_pipe, d, N_pipe, &pos);
        else if ((*d).cmd_state[pos] == BUILT_IN)
            exec_built_inpipe(var_pipe, d, N_pipe, &pos);
        pos++;
    }
    close_pipe(var_pipe, N_pipe, 0);
    pos = 0;
    while (pos <= N_pipe)
    {
        wait(NULL);
        pos++;
    }
}
