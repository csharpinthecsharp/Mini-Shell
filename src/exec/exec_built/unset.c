/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:17:48 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 12:44:57 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int handle_unset(char **argv, int count, t_data *d)
{
    if (count == 1)
        return (0);
    
    int pos = 1;
    while (pos < count)
    {
        int i = 0;
        while (d->envp[i])
        {
            int len = ft_strlen(argv[pos]);
            if (ft_strncmp(argv[pos], d->envp[i], len) == 0
                && d->envp[i][len] == '=')
            {
                free(d->envp[i]);

                int j = i;
                while (d->envp[j + 1])
                {
                    d->envp[j] = d->envp[j + 1];
                    j++;
                }
                d->envp[j] = NULL;
                break;
            }
            i++;
        }
        pos++;
    }
    return (0);
}
