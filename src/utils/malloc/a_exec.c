/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:12:13 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/21 13:01:50 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void alloc_start_execution(t_data *d)
{
    alloc_cmd_state(d);
    alloc_redir_state(d);
    alloc_output_file(d);
}

void alloc_cmd_state(t_data *d)
{
    d->cmd_state = malloc(sizeof(int) * d->cmd_count + 1);
    if (!d->cmd_state)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
}

void alloc_redir_state(t_data *d)
{
    d->redirection_state = malloc(sizeof(int *) * 64);
    if (!d->redirection_state)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i <= (d->cmd_count + 1))
    {
        d->redirection_state[i] = malloc(sizeof(int) * 2);
        if (!d->redirection_state[i])
        {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

#define MAX_CMDS 64
#define MAX_REDIRS 64
#define MAX_FILENAME_LEN 64

void alloc_output_file(t_data *d)
{
    d->output_file = malloc(sizeof(char **) * MAX_CMDS);
    if (!d->output_file)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_FILENAME_LEN; i++)
    {
        d->output_file[i] = malloc(sizeof(char *) * MAX_FILENAME_LEN);
        if (!d->output_file[i])
        {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < MAX_REDIRS; j++)
        {
            d->output_file[i][j] = malloc(sizeof(char) * (MAX_REDIRS + 1));
            if (!d->output_file[i][j])
            {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }
        }
    }
}
 