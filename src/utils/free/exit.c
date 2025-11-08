/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:41:34 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/31 16:36:10 by ltrillar         ###   ########.fr       */
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

static void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

static void	free_redirs(t_cmd *cmd)
{
	int	i;

	if (!cmd->arguments)
		return ;
	i = -1;
	while (++i < cmd->nb_redir)
		free(cmd->arguments[i].file);
	free(cmd->arguments);
}

void	free_cmds(t_data *d)
{
	int	i;

	if (!d || !d->cmd)
		return ;
	i = -1;
	while (++i < d->nb_cmd)
	{
		free_args(d->cmd[i].arg);
		free_redirs(&d->cmd[i]);
	}
	free(d->cmd);
	d->cmd = NULL;
}

void	free_all(t_data *d)
{
	if (d->term_saved)
		tcsetattr(STDIN_FILENO, TCSANOW, &d->original_term);
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
