/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_x_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:15:19 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 15:25:14 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int right_helper(char *dir, t_cmd *c, t_data *d, int i)
{
	if (!dir || access(dir, F_OK) != 0)
	{
		if (i == c->nb_redir)
			return (FAILED);
		else
			check_status_error(d, c->arguments[i].file,
				"No such file or directory");
	}
	if (access(c->arguments[i].file, F_OK) == 0
		&& access(c->arguments[i].file, W_OK) != 0)
	{
		if (errno == EACCES)
		{
			if (i == c->nb_redir)
				return (FAILED);
			else
				check_status_error(d, c->arguments[i].file,
					"Permission denied");
		}
	}
	return (SUCCESS);
}
int	check_dir_right(t_cmd *c, t_data *d, char *dir, int i)
{
	if ((c->arguments[i].state_redir == RIGHT
			|| c->arguments[i].state_redir == RIGHT_RIGHT)
		&& c->arguments[i].file)
	{
		if (right_helper(dir, c, d, i) == FAILED)
			return (FAILED);
	}
	return (SUCCESS);
}

static int	check_dir(t_cmd *cmd, t_data *d, char *dir, int i)
{
	if (!dir)
		return (FAILED);
	if (check_dir_right(cmd, d, dir, i) == FAILED)
	{
		free(dir);
		return (FAILED);
	}
	else if (check_dir_left(cmd, d, cmd->arguments[i].file, i) == FAILED)
	{
		free(dir);
		return (FAILED);
	}
	free(dir);
	return (SUCCESS);
}

int	check_output_ofeach(t_cmd *cmd, t_data *d)
{
	int		i;
	char	*dir;

	i = 0;
	while (i < cmd->nb_redir)
	{
		if (cmd->arguments[i].file == NULL)
		{
			i += 1;
			continue ;
		}
		dir = get_directory(cmd->arguments[i].file);
		if (!dir)
			return (FAILED);
		if (check_dir(cmd, d, dir, i) == FAILED)
			return (FAILED);
		i++;
	}
	return (SUCCESS);
}