/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:11:43 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/27 14:16:33 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int getpath()
{
    char buffer[BUFFER_SIZE];
    if (getcwd(buffer, BUFFER_SIZE) == NULL)
    {
        printf("Error: \nSomething went wrong will "
             "retrieving the current path.");
        return (1);
    }
    printf("%s", buffer);
    return (0);
}