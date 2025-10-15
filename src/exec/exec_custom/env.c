/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:39:38 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 12:39:47 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int handle_env(char **argv, int count, t_data *d)
{
    (void)argv;
    if (count == 1)
    {
        int i = 0;
        while (d->envp[i])
        {
            printf("%s\n", d->envp[i]);
            i++;
        }
    }
    return (0);
}