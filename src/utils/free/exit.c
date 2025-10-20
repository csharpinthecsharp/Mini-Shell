/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:41:34 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/20 17:29:10 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	free_cmds(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (d->commands[i])
	{
		j = 0;
		while (d->commands[i][j])
		{
			free(d->commands[i][j]);
			j++;
		}
		free(d->commands[i]);
		i++;
	}
	free(d->commands);
}

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

void	free_all(t_data *d, char *buffer)
{
	if (d->cmd_state)
		free(d->cmd_state);
	if (d->commands)
		free_cmds(d);
	if (d->input)
		free(d->input);
	if (d->envp)
		free_envp(d);
	if (d->input_splitted)
		free_splitted(d);
	rl_clear_history();
	free(d->path);
	free(buffer);
}
