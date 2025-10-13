/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 20:43:24 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/template.h"

int main(int ac, char *av[], char *envp[])
{
    (void)av;
    if (ac != 1)
        return (EXIT_FAILURE);
    char *buf = NULL;
    alloc_buffer(&buf);
    t_data data;
    t_data *d = &data;
    init_data(d);
    d->envp = duplicate_envp(envp);
    prepare_signals();
    while (1)
    {
        update_data(d);
        d->path = getpath(buf, d);
        select_readline_mode(d);
        if (!d->input)
            break;
        if (start_minishell(d) == 1)
            exit(EXIT_FAILURE);
        free_beforenewline(d, buf);
    }
    free_all(d, buf);
    return (EXIT_SUCCESS);
}

