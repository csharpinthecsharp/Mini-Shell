/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:49:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/14 01:13:08 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void redirect_right(t_data *d, int *pos, int fd_out)
{
    fd_out = open(d->output_file[*pos], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0)
    {
        print_error("No such file or directory", d->output_file[*pos]);
        d->exit_status = 1;
        exit(1);
    }
    else
    {
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}

void redirect_right_right(t_data *d, int *pos, int fd_out)
{
    fd_out = open(d->output_file[*pos], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_out < 0)
    {
        print_error("No such file or directory", d->output_file[*pos]);
        d->exit_status = 1;
        exit(1);
    }
    else
    {
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}

void redirect_left(t_data *d, int *pos, int fd_in)
{
    fd_in = open(d->output_file[*pos], O_RDONLY);
    if (fd_in < 0)
    {
        print_error("No such file or directory", d->output_file[*pos]);
        d->exit_status = 1;
        exit(1);
    }
    else
    {
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
}

void redirect_left_left(t_data *d, int *pos, int fd_in)
{
    (void)fd_in;
    char *res = NULL;
    char *delimiter = d->output_file[*pos];
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
    }
      
    d->kill_heredoc = 0;
    d->in_heredoc = 1;

    while (1)
    {
        if (d->kill_heredoc == 1)
        {
            d->kill_execution = 0;
            break;
        }
        res = readline("> ");
        if (!res)
        {
            print_error("here-document delimited by end-of-file", "warning");
            break;
        }
        if (strcmp(res, delimiter) == 0)
        {
            free(res);
            break;
        }
        write(pipefd[1], res, strlen(res));
        write(pipefd[1], "\n", 1);
        free(res);
    }
    d->in_heredoc = 0;
    close(pipefd[1]);
    close(pipefd[0]);
    d->exit_status = 0;
}


int is_redirect(char **argv, t_data *d)
{
    int i = 0;
    int count_left = 0;
    int count_right = 0;
    while (argv[i])
    {
        if (ft_strncmp(argv[i], ">", 2) == 0)
            count_right++;
        else if (ft_strncmp(argv[i], "<", 2) == 0)
            count_left++;
        i++;
    }
    d->N_redir = (count_left + count_right);
    
    if (count_left == 1 && count_right == 0)
        return (LEFT);
    else if (count_left == 2 && count_right == 0)
        return (LEFT_LEFT);
    else if (count_left == 0 && count_right == 1)
        return (RIGHT);
    else if (count_left == 0 && count_right == 2)
        return (RIGHT_RIGHT);
    else
        return (NOT_FOUND);
}
