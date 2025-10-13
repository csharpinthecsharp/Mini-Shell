/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:16:28 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/14 01:09:41 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data *g_data = NULL;

void handler_ctrl_c(int sig)
{
    (void)sig;

    if (g_data->in_heredoc == 1)
    {
        g_data->kill_heredoc = 1;
        g_data->in_heredoc = 0;
        g_data->kill_execution = 1;
        return;
    }
    write(STDOUT_FILENO, "^C\n", 3);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}


void handler_ctrl_bs(int sig)
{
    (void)sig;
}

void prepare_signals(t_data *d)
{
    rl_catch_signals = 0;
    g_data = d;
    signal(SIGINT, handler_ctrl_c);
    signal(SIGQUIT, handler_ctrl_bs);
}