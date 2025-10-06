/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 20:18:18 by ltrillar         ###   ########.fr       */
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

    printf(TEMPLATE_SETUP_SCREEN);
    while (1)
    {
        // RESET VALEUR POUR LE NOUVEAU INPUT
        update_data(d);
        
        d->path = getpath(buf);

        d->input = readline(get_promptpath(buf)); 
        // Si EOF on sors de la boucle.
        // EOF = CTRL D.
        if (!d->input)
            break;
        // Ajouter a l'historique.
        if (*d->input)
            add_history(d->input);   
        // Si la commande n'est pas a built in,
        // Et est connu de notre base, on la run.
        // Exemple [cat, ls].
        // NON BUILD IN COMMAND
        if (filter_input(d) == 1)
            exit(EXIT_FAILURE);
    }
    free(buf);
    free_all(d);
    return (EXIT_SUCCESS);
}

