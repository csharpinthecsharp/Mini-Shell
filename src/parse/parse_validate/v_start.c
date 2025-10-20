/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:46:28 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/20 17:34:01 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	global_check(t_data *d)
{
	if (check_pipe_syntax(d->input) == FAILED)
	{
		d->exit_status = 2;
		return (FAILED);
	}
	if (check_redirection_syntax(d->input) == FAILED)
	{
		d->exit_status = 2;
		return (FAILED);
	}
	return (SUCCESS);
}
