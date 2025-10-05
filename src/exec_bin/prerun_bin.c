/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prerun_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:05:56 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 15:16:49 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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