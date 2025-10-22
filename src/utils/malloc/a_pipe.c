/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:38:50 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 16:43:10 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void alloc_error_pipe(int N_pipe, int **var_pipe)
{
    int i = 0;
    while (i < N_pipe)
    {
        var_pipe[i] = malloc(sizeof(int) * 2);
        if (!var_pipe[i])
        {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        if (pipe(var_pipe[i]) == -1)
        {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}
