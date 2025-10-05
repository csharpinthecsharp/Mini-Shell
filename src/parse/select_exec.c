/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:57:15 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 20:38:09 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_command(char **argv)
{
    // return 0 = on a pas trouvé de commande dedans.
    // return 1 = on a trouvé une commande qu'il faut build.
    // return 2 = pas besoin de la build, juste execve.
    int len = ft_strlen(argv[0]);
    if (ft_strncmp(argv[0], "pwd", len) == 0)
        return (FAILED);
    else if (ft_strncmp(argv[0], "exit", len) == 0)
        return (FAILED);
    else if (ft_strncmp(argv[0], "echo", len) == 0)
        return (FAILED);
    else if (ft_strncmp(argv[0], "cd", len) == 0)
        return (FAILED);
    else if (ft_strncmp(argv[0], "export", len) == 0)
        return (FAILED);
    return (SUCCESS);
}

static int is_valid_bin(char *str)
{
    char *bin = ft_strdup(ft_strjoin("/bin/", str));
    int fd = open(bin, O_RDONLY);
    if (fd < 0)
        return (FAILED);
    return (SUCCESS);
}

int select_type(t_data *d)
{
    if (check_command(d->input_splitted) == FAILED)
    {
        if (run_custom_cmd(d) == FAILED)
            return (FAILED);
    }
    else if (check_command(d->input_splitted) == SUCCESS)
    {
        if (is_valid_bin(d->input_splitted[0]) == SUCCESS)
        {
            if (run_build_cmd(d, d->envp) == FAILED)
                return (FAILED);
        }
        else
            print_error("command not found: ", d->input_splitted[0]);
    }
    return (0);
}
