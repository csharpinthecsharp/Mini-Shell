/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:57:15 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/04 23:23:05 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_command(char **argv)
{
    // return 0 = on a pas trouvé de commande dedans.
    // return 1 = on a trouvé une commande qu'il faut build.
    // return 2 = pas besoin de la build, juste execve.
    int len = ft_strlen(argv[0]);
    if (ft_strncmp(argv[0], "pwd", len) == 0)
        return (1);
    else if (ft_strncmp(argv[0], "exit", len) == 0)
        return (1);
    else if (ft_strncmp(argv[0], "echo", len) == 0)
        return (1);
    else if (ft_strncmp(argv[0], "cd", len) == 0)
        return (1);
    else
        return (2);
    return (0);
}

int run_custom_cmd(t_data *d)
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    int count = 0;

    while (d->input_splitted[count])
        count++;
    if (ft_strncmp(d->input_splitted[0], "pwd", 3) == 0)
    {
        if (handle_pwd(d->input_splitted[0], count, d->path) == 1)
            return (1);
    }
    else if (ft_strncmp(d->input_splitted[0], "exit", 4) == 0)
    {
        if (handle_exit(d->input_splitted[0], count) == 1)
            return (1);
    }
    else if (ft_strncmp(d->input_splitted[0], "echo", 4) == 0)
    {
        if (handle_echo(d->input_splitted, count) == 1)
            return (1);
    }
    else if (ft_strncmp(d->input_splitted[0], "cd", 2) == 0)
    {
        if (handle_cd(d->input_splitted, count, d) == 1)
            return (1);
    }
    return (0);
}

int run_build_cmd(t_data *d, char *envp[])
{
        d->commands = split_commands(d->input_splitted);
        if (d->commands == NULL)
            return (1);
        
        int cmds = 0;
        int count = 0;
        while (d->commands[cmds])
        {
            while (d->commands[cmds][count])
                count++;
            char *argv = malloc(sizeof(char *) * count + 2);
            if (!argv)
                return (1);
            argv = ft_strjoin("/bin/", d->commands[cmds][0]);
            d->commands[cmds][0] = argv;
            cmds++;
        }
    
        pipe_the_pipe(d->commands, envp, pipe_count(d->input_splitted));
    
        return (0);
}