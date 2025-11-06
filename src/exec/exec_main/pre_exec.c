/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/06 15:33:30 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	pre_exec_error(t_data *d, int status)
{
	d->defer_errors = 0;
	flush_deferred_errors(d);
	return (status);
}

static int	pre_exec_state(t_data *d, int i, int *is_stateful)
{
	int	type;

	type = check_command(d->cmd[i].arg, d);
	if (put_cmdstate(type, is_stateful, &d->cmd[i], d) == FAILED)
		return (pre_exec_error(d, FAILED));
	return (SUCCESS);
}

int	pre_execution(t_data *d)
{
	int	is_stateful;
	int	i;
	int	res;

	res = 0;
	d->defer_errors = 1;
	is_stateful = 0;
	i = 0;
	while (i < d->nb_cmd)
	{
		res = pre_exec_prepare(d, i);
		if (res == ERROR)
			return (ERROR);
		else if (res == FAILED)
			return (FAILED);
		res = pre_exec_state(d, i, &is_stateful);
		if (res == ERROR || res == FAILED)
			return (FAILED);
		i++;
	}
	d->defer_errors = 0;
	if (is_stateful == 0)
		start_execution(d);
	flush_deferred_errors(d);
	return (SUCCESS);
}
