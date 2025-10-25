/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 01:43:38 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../include/minishell.h"

static int allocate_t_arguments(t_cmd *cmd)
{
    int nb_redir = count_redir(cmd->arg);
    cmd->nb_redir = nb_redir;

    if (nb_redir > 0) 
    {
        cmd->arguments = calloc(nb_redir, sizeof *cmd->arguments);
        if (!cmd->arguments)
            return FAILED;
    } 
    else 
        cmd->arguments = NULL;
    return (SUCCESS);
}

static int fill_arguments(t_data *d, t_cmd *cmd, int cmd_index)
{
    if (cmd->nb_redir > 0)
    {
        int k = 0;
        for (int j = 0; j < cmd->nb_arg; j++) 
        {
            if (put_redir(d, cmd_index, j, k)) {
                k++;
            }
        }
        cmd->nb_redir = k;
    }
    return (SUCCESS);
}

static int cut_redirection_command(t_cmd *cmd)
{
    if (cmd->nb_redir > 0) 
    {
        char **old = cmd->arg;
        char **clean = fix_redir_arg(cmd);

        int i = 0;
        while (old[i]) 
        {
            free(old[i]);
            i++;
        }
        free(old);

        cmd->arg = clean;
    }
    return (SUCCESS);
}

int pre_execution(t_data *d)
{
    int is_stateful = 0;

    int i = 0;
    while (i < d->nb_cmd) 
    {
        if (allocate_t_arguments(&d->cmd[i]) == FAILED)
            return (ERROR);
        if (fill_arguments(d, &d->cmd[i], i) == FAILED)
            return (ERROR);
        if (cut_redirection_command(&d->cmd[i]) == FAILED)
            return (ERROR);
        if (is_empty(d, i, 0) == FAILED)
            return (FAILED);
        int type = check_command(d->cmd[i].arg, d);
        if (put_cmdstate(type, &is_stateful, &d->cmd[i], d) == FAILED) {
            return (FAILED);
        }
        i++;
    }
    if (is_stateful == 0)
        start_execution(d);
    return (SUCCESS);
}
