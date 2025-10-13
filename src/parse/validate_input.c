/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:46:28 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 13:16:22 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int pipe_check(char *input, int *pos)
{
    (void)pos;
    if (input[*pos] == PIPE)
    {
        print_error("syntax error near unexpected token `|'", "!");
        return (1);
    } 
    return (0);
}

int global_check(t_data *d)
{
    int pos = 0;
    if (pipe_check(d->input, &pos) == 1)
    {
        d->exit_status = 2;
        return (1);
    }
    return (0);
}
