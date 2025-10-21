/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/21 15:58:58 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char **get_args(char *s, t_data *d)
{
    int i = 0;
    int k = 0;
    int is_dquote = 0;
    int len = ft_strlen(s);
    char **argv;
    argv = NULL;
    alloc_parse_args(&argv, len);
    while (s[i])
    {
        char *raw_arg = get_one_arg(s, &i, &is_dquote);
        if (!raw_arg)
            break;
        char *arg = replace_envvar(raw_arg, d, &is_dquote);
        free(raw_arg);
        if (!arg)
            break;
        argv[k++] = arg;
    }
    argv[k] = NULL;
    return argv;
}

static int count_commands(char **argv)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (argv[i])
    {
        if (ft_strncmp(argv[i], "|", 2) == 0)
            count++;
        i++;
    }
    return (count + 1);
}

static int count_arg(char **argv, int i)
{
    int count = 0;
    while (argv[i] && ft_strncmp(argv[i], "|", 2) != 0)
    {
        count++;
        i++;
    }
    return count;
}

int split_commands(char **argv, t_data *d)
{
    int arg_index = 0; // index in argv
    int cmd_index = 0; // command index

    d->nb_cmd = count_commands(argv);
    d->cmd = malloc(sizeof(t_cmd) * d->nb_cmd);
    if (!d->cmd)
        return (-1);

    while (cmd_index < d->nb_cmd)
    {
        int j = 0;

        d->cmd[cmd_index].nb_arg = count_arg(argv, arg_index); // must count until next '|'
        d->cmd[cmd_index].arg = malloc(sizeof(char *) * (d->cmd[cmd_index].nb_arg + 1));
        if (!d->cmd[cmd_index].arg)
            return (-1);

        while (argv[arg_index] && ft_strncmp(argv[arg_index], "|", 2) != 0)
            d->cmd[cmd_index].arg[j++] = ft_strdup(argv[arg_index++]);

        // Null-terminate without incrementing j
        d->cmd[cmd_index].arg[j] = NULL;

        // Skip the pipe token if present
        if (argv[arg_index] && ft_strncmp(argv[arg_index], "|", 2) == 0)
            arg_index++;

        cmd_index++;
    }

    if (argv) {
        for (int a = 0; argv[a]; a++)
            free(argv[a]);
        free(argv);
    }
    return SUCCESS;
}



char **split(t_data *d)
{
    char **argv = get_args(d->input, d);
    if (!argv)
        return (NULL);
    return (argv);
}

