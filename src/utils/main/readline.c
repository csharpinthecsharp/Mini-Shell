/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:56:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/23 17:22:21 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/template.h"

void	select_readline_mode(t_data *d)
{
	char	*res;

	if (isatty(STDIN_FILENO))
	{
		res = get_promptpath(d);
		d->input = readline(res);
		free(res);
	}
	else
		d->input = readline("minishell: ");
}

void	start_minishell(t_data *d)
{
	if (ft_strlen(d->input) != 0 && !isfulls(d->input))
	{
		if (*d->input)
			add_history(d->input);
		if (start_point_parsing(d) == 1)
			return ;
	}
}

void	exit_ctrl_d(t_data *d)
{
	if (!d->input)
	{
		printf("exit\n");
		free_all(d);
		exit(d->exit_status);
	}
}
