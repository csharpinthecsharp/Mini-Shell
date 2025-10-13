/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:39:16 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 12:42:32 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int handle_export(char **argv, int count, t_data *d)
{
    if (count == 1)
    {
        int i = 0;
        while (d->envp[i])
        {
            printf("%s\n", d->envp[i]);
            i++;
        }
        return (0);
    }
    if (count == 2)
    {
        int p = 0;
        while (argv[1][p])
        {
            if (argv[1][p] == '=')
                break;
            if ((argv[1][p] >= 'a' && argv[1][p] <= 'z')
                || (argv[1][p] >= 'A' && argv[1][p] <= 'Z'))
                p++;
            else
            {
                print_error("not a valid identifier", argv[1]);
                return (1);
            }
        }
        
        if (is_numeric(argv[1]) || argv[1][0] == '=')
        {
            print_error("not a valid identifier", argv[1]);
            return (1);
        }
        
        int i = 0;
        while (d->envp[i])
            i++;
        char **new_envp = realloc(d->envp, sizeof(char *) * (i + 2));
        if (!new_envp)
            return (1);
            
        d->envp = new_envp;

        d->envp[i] = malloc(sizeof(char ) * ft_strlen(argv[1]) + 1);
        if (!d->envp[i])
            return (1);
        
        int j = 0;
        while (argv[1][j])
        {
            d->envp[i][j] = argv[1][j];
            j++;
        }
        d->envp[i][j] = '\0';
        i += 1; // Go to NULL.
        d->envp[i] = NULL;
    }
    return (0);
}
