/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 20:15:42 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/template.h"

void handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
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
    d->envp = envp;
    // CTRL C = NEWLINE
    signal(SIGINT, handler);
    
    printf(TEMPLATE_SETUP_SCREEN);
    while (1)
    {
        // RESET VALEUR POUR LE NOUVEAU INPUT
        update_data(d);
        
        d->path = getpath(buffer);

        d->input = readline(get_promptpath(buffer)); 
        // Si EOF on sors de la boucle.
        // EOF = CTRL D.
        if (!d->input)
            exit(EXIT_SUCCESS);
        // Ajouter a l'historique.
        if (*d->input)
            add_history(d->input);   
        // Si la commande n'est pas a built in,
        // Et est connu de notre base, on la run.
        // Exemple [cat, ls].
        // NON BUILD IN COMMAND
        if (filter_input(d) == 1)
            exit(EXIT_FAILURE);
             
        free(d->input);
        free(d->path);
    }
    return (EXIT_SUCCESS);
}

