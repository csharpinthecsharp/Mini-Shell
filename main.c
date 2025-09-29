/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/29 13:27:23 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// REPL 
// R = READ | E = EVALUATE | P = EXECUTE | L = LOOP.
int main(int ac, char *av[], char *envp[])
{
    if (ac != 1)
        return (EXIT_FAILURE);
    (void)av;
    
    char buffer[BUFFER_SIZE];
        
    t_data data;
    t_data *d = &data;
    
    printf(TEMPLATE_SETUP_SCREEN);
    while (1)
    {
        d->path = getpath(buffer);

        d->input = readline(TEMPLATE_PROMPT);        
        // Si EOF on sors de la boucle.
        // EOF = CTRL D.
        if (!d->input)
        {
            printf(TEMPLATE_GOOD_BYE);
            exit(EXIT_SUCCESS);
        }
        // Si la commande n'est pas a built in,
        // Et est connu de notre base, on la run.
        // Exemple [cat, ls].

        // NON BUILD IN COMMAND
        if (filter_input(d, envp) == 1)
            exit(EXIT_FAILURE);
        
        // Ajouter a l'historique.
        add_history(d->input);
        
        free(d->input);
        free(d->path);
    }
    return (EXIT_SUCCESS);
}

