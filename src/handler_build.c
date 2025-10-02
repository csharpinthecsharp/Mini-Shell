/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:17:48 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/02 16:24:22 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int handle_pwd(char *argv, int count, char *path)
{
    if (count != 1)
    {
        print_error(argv, ": too many arguments");
        return (0);
    }
    printf("%s\n", path);
    return (0);
}

int handle_exit(char *argv, int count)
{
    if (count == 1)
        exit(EXIT_SUCCESS);
    else if (count == 2 && ft_atoi(argv) > 0)
        exit(EXIT_FAILURE);
    else
        print_error(argv, ": too many arguments");
    return (0);
}

int handle_echo(char **argv, int count)
{
    if (count == 1)
        printf("\n");
    int i = 1;
    if (count >= 2)
    {
        while (i < count)
        {
            if (i >= 2)
                printf(" ");
            printf("%s", argv[i]);
            i++;
        }
        printf("\n");
    }
    return (0);
}