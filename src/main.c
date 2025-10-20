/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/20 11:56:46 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/template.h"

int	main(int ac, char *av[], char *envp[])
{
	char	*buf;
	t_data	data;
	t_data	*d;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	buf = NULL;
	alloc_buffer(&buf);
	d = &data;
	init_data(d);
	prepare_signals();
	d->envp = duplicate_envp(envp);
	while (1)
	{
		update_data(d);
		d->path = getpath(buf, d);
		select_readline_mode(d);
		exit_ctrl_d(d, buf);
		start_minishell(d);
		free_beforenewline(d, buf);
	}
	free_all(d, buf);
	return (EXIT_SUCCESS);
}
