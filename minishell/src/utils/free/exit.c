/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrezette <lrezette@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:41:34 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/27 21:42:20 by lrezette         ###   ########.fr       */
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
	d->envp = NULL;
}

void	free_cmds(t_data *d)
{
	int	i;
	int	j;
	int	k;

	if (!d || !d->cmd)
		return ;
	for (i = 0; i < d->nb_cmd; i++)
	{
		if (d->cmd[i].arg)
		{
			j = 0;
			while (d->cmd[i].arg[j])
				free(d->cmd[i].arg[j++]);
			free(d->cmd[i].arg);
			d->cmd[i].arg = NULL;
		}
		if (d->cmd[i].arguments)
		{
			k = 0;
			while (k < d->cmd[i].nb_redir)
			{
				if (d->cmd[i].arguments[k].file)
					free(d->cmd[i].arguments[k].file);
				k++;
			}
			free(d->cmd[i].arguments);
			d->cmd[i].arguments = NULL;
		}
	}
	free(d->cmd);
	d->cmd = NULL;
}

void	free_all(t_data *d)
{
	if (d->input)
		free(d->input);
	if (d->envp)
		free_envp(d);
	if (d->cmd)
	{
		free_cmds(d);
		d->nb_cmd = 0;
	}
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
