/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_built.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:17:48 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/11 14:28:53 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

static int is_numeric(const char *str)
{
    int i = 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int handle_exit(char **argv, int count)
{
    (void)count;
    if (!argv[1])
        exit(0);

    if (!is_numeric(argv[1]))
    {
        print_error("numeric argument required", argv[1]);
        exit(2);
    }

    if (argv[2])
    {
        print_error("too many arguments", argv[0]);
        return 1;
    }

    exit(ft_atoi(argv[1]) % 256);
}

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

#define PATH "/home/vez"
int handle_cd(char **argv, int count, t_data *d)
{
    if (count == 1)
    {
        if (chdir(PATH) != 0)
        {
            print_error("Error: ", strerror(errno));
        }
    }
    else
    {
        char *oui = ft_strdup(ft_strjoin(d->path, "/"));
        char *test = ft_strdup(ft_strjoin(oui, argv[1]));
        if (chdir(test) != 0)
        {
            print_error("Error: ", strerror(errno));
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

int handle_unset(char **argv, int count, t_data *d)
{
    (void)count;
    (void)d;
    (void)argv;
    return (0);
}