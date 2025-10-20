/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:16:28 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/20 17:30:25 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handler_ctrl_c(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	heredoc_ctrl_c(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_done = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_cleanup_after_signal();
	exit(0);
}

void	handler_ctrl_bs(int sig)
{
	(void)sig;
}

void	prepare_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handler_ctrl_c);
	signal(SIGQUIT, handler_ctrl_bs);
}
