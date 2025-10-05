/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_built.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:17:48 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 16:37:44 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int handle_exit(char **argv, int count)
{
    if (count == 1)
        exit(EXIT_SUCCESS);
    else if (count == 2)
    {
        exit(atoi(argv[1]));
    }
    else
        print_error(argv[0], ": too many arguments");
    return (0);
}

int handle_echo(char **argv, int count)
{
    if (count < 2)
        printf("\n");
    else
    {
        int i = 1;
        while (i < count)
        {
            if (i > 1)
                printf(" ");
            printf("%s", argv[i]);
            i++;
        }
    }
    printf("\n");
    return (0);
}

#define PATH "/home/vez"
int handle_cd(char **argv, int count, t_data *d)
{
    if (count == 1)
    {
        if (chdir(PATH) != 0)
        {
            print_error("Error: ", strerror(errno));
            return (1);
        }
    }
    else
    {
        char *oui = strdup(ft_strjoin(d->path, "/"));
        char *test = strdup(ft_strjoin(oui, argv[1]));
        if (chdir(test) != 0)
        {
            print_error("Error: ", strerror(errno));
            return (1);
        }
    }
    return (0);
}

// UPDATE_ENVP
// struct s_envp avec une key par value et un bool 
// qui dis si la valeur est export ou non.

int handle_export(char **argv, int count, t_data *d)
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