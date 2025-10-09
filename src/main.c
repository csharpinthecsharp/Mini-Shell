/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/10 01:08:36 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/template.h"

// REPL
// R = READ | E = EVALUATE | P = EXECUTE | L = LOOP.
int main(int ac, char *av[], char *envp[])
{
    if (ac != 1)
        return (EXIT_FAILURE);
    (void)av;
    char *buf = malloc(sizeof(char) * BUFFER_SIZE);
    if (!buf)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    t_data data;
    t_data *d = &data;
    d->envp = envp;
    prepare_signals();
    while (1)
    {
        update_data(d);
        d->path = getpath(buf);
        d->input = readline(get_promptpath(buf)); 
        if (!d->input)
            break;
        if (*d->input)
            add_history(d->input);   
        if (filter_input(d) == 1)
            exit(EXIT_FAILURE);
        free(d->path);
        free(d->input);
    }
    free(buf);
    free_all(d);
    return (EXIT_SUCCESS);
}

