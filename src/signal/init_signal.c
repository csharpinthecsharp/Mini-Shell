/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:16:28 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/10 22:54:54 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handler_ctrl_c(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "^C\n", 3);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void handler_ctrl_bs(int sig)
{
    (void)sig;
}

void prepare_signals(void)
{
    // set rl signal to 0 so she don't
    // overwrite SIGINT OR SIGQUIT.
    rl_catch_signals = 0;
    signal(SIGINT, handler_ctrl_c);
    signal(SIGQUIT, handler_ctrl_bs);
}