/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prerun_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:05:56 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 14:46:27 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int run_build_cmd(t_data *d)
{       
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
    return (0);
}
