/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:35:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/14 17:35:48 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/template.h"

void update_data(t_data *d)
{
    d->kill_heredoc = 0;
    d->in_heredoc = 0;
    d->input = NULL;
    d->input_splitted = NULL;
    d->path = NULL;
    d->commands = NULL;
    d->cmd_state = NULL;
    d->cmd_count = 0;
    d->N_redir = 0;
    d->new_path = NULL;
    d->stdin_back = -1;
}

void init_data(t_data *d)
{
    d->kill_execution = 0;
    d->kill_heredoc = 0;
    d->exit_status = 0;
    d->input = NULL;
    d->input_splitted = NULL;
    d->path = NULL;
    d->commands = NULL;
    d->cmd_state = NULL;
    d->cmd_count = 0;
    d->N_redir = 0;
    d->new_path = NULL;
}

void select_readline_mode(t_data *d)
{
    if (isatty(STDIN_FILENO))
    {
        d->input = readline(get_promptpath(d->path, d));
    }
    else
    {
        d->input = readline("minishell > ");
    }
}

int start_minishell(t_data *d)
{
    if (d->kill_execution == 1)
        return 0;
    if (ft_strlen(d->input) != 0 && !isfulls(d->input))
    {
        if (*d->input)
            add_history(d->input);   
        start_point_parsing(d);
    }
    return (SUCCESS);
}