/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_custom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:09:41 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 15:17:04 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	error_export(char *equal_sign, char **arg_ptr)
{
	if (!equal_sign)
	{
		if (!is_valid_identifier(*arg_ptr))
		{
			print_error("not a valid identifier", *arg_ptr);
			return (FAILED);
		}
		*arg_ptr = ft_strjoin(*arg_ptr, "=''");
	}
	if ((*arg_ptr[0]) == '=' || !is_valid_identifier(*arg_ptr))
	{
		print_error("not a valid identifier", *arg_ptr);
		return (FAILED);
	}
	return (SUCCESS);
}

void	check_status_error(t_data *d, char *file, char *error_s)
{
	if (!d)
		return ;
	d->exit_status = 1;
	if (isatty(STDIN_FILENO))
		print_error(error_s, file);
	else if (d->error_state == 0 && !isatty(STDIN_FILENO))
	{
		print_error(error_s, file);
		d->error_state = 1;
	}
}
