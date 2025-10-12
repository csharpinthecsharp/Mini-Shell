/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/12 01:17:23 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/template.h"

static int isfulls(char *s)
{
    size_t i = 0;
    while (ft_isspace(s[i]))
        i++;
    if (ft_strlen(s) == i)
        return (1);
    else
        return (0);
}

static char *up_shlvl(char *envp_i)
{
    if (ft_strncmp(envp_i, "SHLVL=1", 9) == 0)
    {
        int lvl = ft_atoi(envp_i + 6);
        lvl++;          
        char *new_lvl = ft_itoa(lvl); 
        char *res = ft_strjoin("SHLVL=", new_lvl);
        free (new_lvl);
        return res;
    }
    else
        return (ft_strdup(envp_i));
}
static char **duplicate_envp(char **envp)
{
    int count = 0;
    while (envp[count])
        count++;
    
    char **argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);
    
    int i = 0;
    while (envp[i])
    {
        argv[i] = up_shlvl(envp[i]);
        if (!argv[i]) 
        {
            while (i > 0)
                free(argv[--i]);
            free(argv);
            return (NULL);
        }
        i++;
    }
    argv[i] = NULL;
    return (argv);
}
// REPL
// R = READ | E = EVALUATE | P = EXECUTE | L = LOOP.
int main(int ac, char *av[], char *envp[])
{
    if (ac != 1)
        return (EXIT_FAILURE);
    (void)av;
    char *buf = malloc(sizeof(char) * 100000);
    if (!buf)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    t_data data;
    t_data *d = &data;

    // DUPLICATE ENVP;
    d->envp = duplicate_envp(envp);
    
    d->exit_status = 0;
    prepare_signals();
    while (1)
    {
        update_data(d);
        d->path = getpath(buf, d);
        // si -> mode interactif on laisse la couleur du prompt.
        // else -> mode script, pour les testeurs par exemple.
        if (isatty(STDIN_FILENO))
            d->input = readline(get_promptpath(d->path, d));
        else
            d->input = readline("minishell > ");

        if (!d->input)
            break;
              
        if (ft_strlen(d->input) != 0 && !isfulls(d->input))
        {
            if (*d->input)
                add_history(d->input);   
            if (filter_input(d) == 1)
                exit(EXIT_FAILURE);
        }
        free(d->path);
        free(d->input);
    }
    free(buf);
    free_all(d);
    return (EXIT_SUCCESS);
}

