/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/28 15:45:57 by ltrillar         ###   ########.fr       */
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
    char *path;
    char *input;
    
    printf(TEMPLATE_SETUP_SCREEN);
    
    while (1)
    {
        path = getpath(buffer);

        input = readline(TEMPLATE_PROMPT);        
        // Si EOF on sors de la boucle.
        // EOF = CTRL D.
        if (!input)
        {
            printf(TEMPLATE_GOOD_BYE);
            exit(EXIT_SUCCESS);
        }
        // Si la commande n'est pas a built in,
        // Et est connu de notre base, on la run.
        // Exemple [cat, ls].

        // NON BUILD IN COMMAND
        try_input(input, envp);

        // BUILD IN COMMAND
        if (ft_strncmp(input, "pwd", 3) == 0)
            printf("%s\n", path);
        if (ft_strncmp(input, "exit", 4) == 0)
        {
            printf(TEMPLATE_GOOD_BYE);
            exit(EXIT_SUCCESS);
        }
        
        // Ajouter a l'historique.
        add_history(input);
        
        free(input);
        free(path);
    }
    return (EXIT_SUCCESS);
}

