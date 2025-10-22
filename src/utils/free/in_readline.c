/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:41:42 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 15:42:39 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void free_split(char **argv)
{
    int i;
    
    i = 0;
    if (argv) 
    {
        while (argv[i])
            free(argv[i++]);
        free(argv);
    }
}