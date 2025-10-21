/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 01:07:11 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 01:16:46 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool is_alone_redir(char **argv, t_data *d)
{
    if (ft_strncmp(argv[0], ">", 2) == 0
        && check_alone_redir(argv) == true)
    {
        d->curr_alone_r = ALONE_R;
        return (true);
    }
    else if (ft_strncmp(argv[0], ">>", 3) == 0
        && check_alone_redir(argv) == true)
    {
        d->curr_alone_r = ALONE_RR;
        return (true);
    }
    else if (ft_strncmp(argv[0], "<", 2) == 0
        && check_alone_redir(argv) == true)
    {
        d->curr_alone_r = ALONE_L;
        return (true);
    }
    else if (ft_strncmp(argv[0], "<<", 3) == 0
        && check_alone_redir(argv) == true)
    {
        d->curr_alone_r = ALONE_LL;
        return (true);
    }
    return (false);
}

int is_available(char *str, t_data *d)
{
    char *res;
    if (ft_strncmp(str, "/bin/", 5) == 0)
        res = str;
    else
        res = ft_strjoin("/bin/", str);

    if (access(res, R_OK) != 0)
    {
        d->exit_status = 127;
        if (res != str)
            free(res);
        return (FAILED);
    }
    if (res != str)
        free(res);
    return (SUCCESS);
}

int is_empty(t_data *d, int cmd_index, int arg_index)
{
    if (d->cmd[cmd_index].nb_redir > 0 &&
        d->cmd[cmd_index].arguments &&
        d->cmd[cmd_index].arguments[arg_index].state_redir == ALONE_REDIR)
    {
        return (SUCCESS);
    }

    if (d->cmd[cmd_index].arg == NULL ||
        d->cmd[cmd_index].arg[arg_index] == NULL)
    {
        d->exit_status = 127;
        print_error("command not found ", "!");
        return FAILED;
    }

    return (SUCCESS);
}