/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:19:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/26 15:15:55 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	start_point_parsing(t_data *d)
{
	int	i;

	if (d->input == NULL)
		return (FAILED);
	if (syntax_validation(d) == 1)
		return (FAILED);
	d->input_splitted = split(d);
	if (d->input_splitted == NULL)
		return (FAILED);
	d->nb_cmd = count_commands(d->input_splitted);
	if (split_commands(d->input_splitted, d) == ERROR)
		return (FAILED);
	i = 0;
	while (i < d->nb_cmd)
	{
		d->cmd[i].arg = remove_empty_var(d->cmd[i].arg);
		i++;
	}
	if (pre_execution(d) == FAILED)
		return (FAILED);
	return (SUCCESS);
}
