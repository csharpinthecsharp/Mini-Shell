/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/27 13:50:04 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
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