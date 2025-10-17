/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_basic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:49:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/17 14:56:57 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void redirect_right(t_data *d, int *pos, int fd_out, int i)
{
    fd_out = open(d->output_file[*pos][i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0)
    {
        print_error("No such file or directory", d->output_file[*pos][i]);
        exit(1);
    }
    else
    {
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}

void redirect_right_right(t_data *d, int *pos, int fd_out, int i)
{
    fd_out = open(d->output_file[*pos][i], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_out < 0)
    {
        print_error("No such file or directory", d->output_file[*pos][i]);
        exit(1);
    }
    else
    {
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}

void redirect_left(t_data *d, int *pos, int fd_in, int i)
{
    fd_in = open(d->output_file[*pos][i], O_RDONLY);
    if (fd_in < 0)
        exit(1);
    else
    {
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
}

int is_redirect(char **argv, t_data *d, int *pos, int i)
{
    int count = 0;

    while (argv[*pos]) 
    {
        int redir_type = NOT_FOUND;

        if (ft_strncmp(argv[*pos], ">>", 3) == 0)
            redir_type = RIGHT_RIGHT;
        else if (ft_strncmp(argv[*pos], ">", 2) == 0)
            redir_type = RIGHT;
        else if (ft_strncmp(argv[*pos], "<<", 3) == 0)
            redir_type = LEFT_LEFT;
        else if (ft_strncmp(argv[*pos], "<", 2) == 0)
            redir_type = LEFT;

        if (redir_type != NOT_FOUND && argv[*pos + 1]) 
        {
            d->redirection_state[i][count] = redir_type;
            d->output_file[i][count] = ft_strdup(argv[*pos + 1]); // store filename
            count++;
            (*pos) += 2; // skip operator and filename
        } 
        else 
        {
            (*pos)++;
        }
    }
    d->N_redir[i] = count;
    return count;
}

