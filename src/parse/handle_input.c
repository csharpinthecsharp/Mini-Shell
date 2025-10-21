/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:19:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 01:23:45 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	start_point_parsing(t_data *d)
{
	if (d->input == NULL)
		return (FAILED);

	if (syntax_validation(d) == 1)
		return (FAILED);

	d->input_splitted = split(d);
	if (d->input_splitted == NULL)
		return (FAILED);

	if (split_commands(d->input_splitted, d) == -1)
		return (FAILED);
	
	if (pre_execution(d) == FAILED)
		return (FAILED);
	return (SUCCESS);
}
