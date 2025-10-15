/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:59:03 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 17:47:10 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char *up_shlvl(char *envp_i)
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
char **duplicate_envp(char **envp)
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