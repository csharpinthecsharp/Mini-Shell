/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec_prepare.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:34:56 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/17 12:34:56 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	allocate_t_arguments(t_cmd *cmd)
{
	int	nb_redir;

	nb_redir = count_redir(cmd->arg);
	cmd->nb_redir = nb_redir;
	if (nb_redir > 0)
	{
		cmd->arguments = ft_calloc(nb_redir, sizeof * cmd->arguments);
		if (!cmd->arguments)
			return (FAILED);
	}
	else
		cmd->arguments = NULL;
	return (SUCCESS);
}

static int	fill_arguments(t_data *d, t_cmd *cmd, int cmd_index)
{
	int	k;
	int	j;

	j = 0;
	if (cmd->nb_redir > 0)
	{
		k = 0;
		while (j < cmd->nb_arg)
		{
			if (put_redir(d, cmd_index, j, k))
			{
				k++;
			}
			j++;
		}
		cmd->nb_redir = k;
	}
	return (SUCCESS);
}

static int	cut_redirection_command(t_cmd *cmd)
{
	char	**old;
	char	**clean;
	int		i;

	if (cmd->nb_redir > 0)
	{
		old = cmd->arg;
		clean = fix_redir_arg(cmd);
		i = 0;
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

static int	pre_exec_prepare_error(t_data *d, int status)
{
	d->defer_errors = 0;
	flush_deferred_errors(d);
	return (status);
}

int	pre_exec_prepare(t_data *d, int i)
{
	if (allocate_t_arguments(&d->cmd[i]) == FAILED)
		return (pre_exec_prepare_error(d, ERROR));
	if (fill_arguments(d, &d->cmd[i], i) == FAILED)
		return (pre_exec_prepare_error(d, ERROR));
	if (cut_redirection_command(&d->cmd[i]) == FAILED)
		return (pre_exec_prepare_error(d, ERROR));
	if (is_empty(d, i, 0) == FAILED)
		return (pre_exec_prepare_error(d, FAILED));
	return (SUCCESS);
}
