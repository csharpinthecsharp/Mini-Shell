/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 01:07:11 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 15:21:29 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	check_alone_redir(char **argv)
{
	int	i;

	i = 0;
	if (argv[i] + 1)
		return (true);
	return (false);
}

int	check_command(char **argv, t_data *d)
{
	bool	res;
	int		len;

	res = is_alone_redir(argv, d);
	if (res == true)
		return (ALONE_REDIR);
	else
		d->curr_alone_r = 0;
	len = ft_strlen(argv[0]);
	if (ft_strncmp(argv[0], "pwd", len) == 0)
		return (CUSTOM);
	else if (ft_strncmp(argv[0], "exit", len) == 0)
		return (STATEFUL);
	else if (ft_strncmp(argv[0], "echo", len) == 0)
		return (CUSTOM);
	else if (ft_strncmp(argv[0], "cd", len) == 0)
		return (STATEFUL);
	else if (ft_strncmp(argv[0], "export", len) == 0)
		return (STATEFUL);
	else if (ft_strncmp(argv[0], "unset", len) == 0)
		return (STATEFUL);
	else if (ft_strncmp(argv[0], "env", len) == 0)
		return (CUSTOM);
	else
		return (BIN);
}

int	check_non_bin(t_cmd *cmd, int type, int *is_stateful, t_data *d)
{
	if (type == CUSTOM)
		cmd->state_cmd = CUSTOM;
	else if (type == ALONE_REDIR)
		cmd->state_cmd = ALONE_REDIR;
	else if (type == STATEFUL)
	{
		*is_stateful = 1;
		if (d->nb_cmd == 1)
			run_custom_cmd(&cmd->arg[0], d);
		else
		{
			d->exit_status = 1;
			return (FAILED);
		}
	}
	return (SUCCESS);
}

int	check_dir_left(t_cmd *cmd, t_data *d, char *file, int i)
{
	if ((cmd->arguments[i].state_redir == LEFT) && file)
	{
		if (access(file, F_OK) != 0)
		{
			if (i == cmd->nb_redir)
				return (FAILED);
			else
				check_status_error(d, file, "No such file or directory");
		}
		if (access(file, R_OK) != 0)
		{
			if (errno == EACCES)
			{
				if (i == cmd->nb_redir)
					return (FAILED);
				else
					check_status_error(d, file, "Permission denied");
			}
		}
	}
	return (SUCCESS);
}
