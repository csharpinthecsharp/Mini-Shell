/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:46:28 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 01:23:54 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	syntax_validation(t_data *d)
{
	if (pipe_syntax(d->input) == FAILED)
	{
		d->exit_status = 2;
		return (FAILED);
	}
	if (redirection_syntax(d->input) == FAILED)
	{
		d->exit_status = 2;
		return (FAILED);
	}
	return (SUCCESS);
}
