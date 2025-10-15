/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:38:26 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 12:38:27 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int handle_echo(char **argv, int count)
{
    int found;
    found = 0;
    if (count < 2)
    {
        printf("\n");
        return (0);
    }
    int i = 1;
    while (i < count)
    {
        if (ft_strncmp(argv[i], "-n", 2) == 0)
            found = 1;
        else
        {
            if (i > 1)
                printf(" ");
            printf("%s", argv[i]);
        }
        i++;
    }
    if (found == 0)
        printf("\n");
    return (0);
}