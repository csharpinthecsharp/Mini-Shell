/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/23 17:33:27 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/template.h"

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;
	t_data	*d;

	(void)av;
	if (ac != 1)
		return (FAILED);
	d = &data;
	init_data(d);
	prepare_signals();
	d->envp = duplicate_envp(envp);
	while (1)
	{
		d->path = get_path(d);
		select_readline_mode(d);
		exit_ctrl_d(d);
		start_minishell(d);
		free_beforenewline(d);
	}
	return (SUCCESS);
}
