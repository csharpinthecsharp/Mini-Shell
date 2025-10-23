/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:41:34 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/23 17:31:41 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	free_envp(t_data *d)
{
	int	i;

	i = 0;
	while (d->envp[i])
	{
		free(d->envp[i]);
		i++;
	}
	free(d->envp);
}

static void	free_splitted(t_data *d)
{
	int	i;

	i = 0;
	while (d->input_splitted[i])
	{
		free(d->input_splitted[i]);
		i++;
	}
	free(d->input_splitted);
}

static void free_cmds(t_data *d)
{
    int i, j, k;

    if (!d->cmd)
        return;

    i = 0;
    while (i < d->nb_cmd)
    {
        if (d->cmd[i].arg)
        {
            j = 0;
            while (j < d->cmd[i].nb_arg)
            {
                free(d->cmd[i].arg[j]);
                j++;
            }
            free(d->cmd[i].arg);
        }
        if (d->cmd[i].arguments)
        {
            k = 0;
            while (k < d->cmd[i].nb_redir)
            {
                free(d->cmd[i].arguments[k].file);
                k++;
            }
            free(d->cmd[i].arguments);
        }
        i++;
    }
    free(d->cmd);
}

void free_all(t_data *d)
{
    if (d->input)
        free(d->input);
    if (d->envp)
        free_envp(d);
    if (d->input_splitted)
        free_splitted(d);
    if (d->cmd)
        free_cmds(d);
    free(d->path);
    free(d->new_path);
    if (d->fd_in > 2)
        close(d->fd_in);
    if (d->fd_out > 2)
        close(d->fd_out);
    if (d->stdin_back > 2)
        close(d->stdin_back);
    rl_clear_history();
}
