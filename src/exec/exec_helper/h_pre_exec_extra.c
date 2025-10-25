/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_pre_exec_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:25:22 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 14:52:56 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	set_error(t_data *d, int exit_code, char *error_s, char *tmp)
{
	d->exit_status = exit_code;
	print_error(error_s, tmp);
}

int	stat_error_h(t_data *d, char *tmp)
{
	struct stat	st;

	if (stat(tmp, &st) == -1)
	{
		if (errno == ENOENT && ft_strchr(tmp, '/') != NULL)
			set_error(d, 127, "No such file or directory", tmp);
		else if (errno == EACCES)
			set_error(d, 126, "Permission denied", tmp);
		else
			set_error(d, 127, "command not found", tmp);
		return (FAILED);
	}
	if (S_ISDIR(st.st_mode))
	{
		if (ft_strchr(tmp, '/') != NULL)
			set_error(d, 126, "Is a directory", tmp);
		else
			set_error(d, 127, "command not found", tmp);
		return (FAILED);
	}
	return (SUCCESS);
}

int	error_h(t_data *d, char *tmp)
{
	if (ft_strchr(tmp, '/') == NULL)
	{
		set_error(d, 127, "command not found", tmp);
		return (FAILED);
	}
	if (stat_error_h(d, tmp) == FAILED)
		return (FAILED);
	if (access(tmp, X_OK) != 0)
	{
		if (errno == EACCES)
			set_error(d, 126, "Permission denied", tmp);
		else
			set_error(d, 127, "command not found", tmp);
		return (FAILED);
	}
	return (SUCCESS);
}
