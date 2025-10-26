/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/26 15:22:07 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**remove_empty_var(char **tokens)
{
	int		count;
	int		i;
	int		j;
	char	**clean;

	i = 0;
	count = 0;
	while (tokens[count])
		count++;
	clean = malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
			clean[j++] = ft_strdup(tokens[i]);
		i++;
	}
	clean[j] = NULL;
	return (clean);
}

static int	break_free(char *arg, char *raw_arg)
{
	if (!arg)
	{
		free(raw_arg);
		return (FAILED);
	}
	else
		free(raw_arg);
	return (SUCCESS);
}

char	**get_args(char *s, t_data *d, int *is_dquote, char **argv)
{
	int		i;
	int		k;
	char	*raw_arg;
	char	*arg;

	i = 0;
	k = 0;
	while (s[i])
	{
		raw_arg = get_one_arg(s, &i, is_dquote);
		if (!raw_arg)
			break ;
		if (ft_strchr(raw_arg, '$'))
		{
			arg = malloc(ft_strlen(raw_arg) + get_expanded_size(s, d));
			arg = replace_envvar(raw_arg, d, is_dquote, arg);
			if (break_free(arg, raw_arg) == FAILED)
				break ;
			argv[k++] = arg;
		}
		else
			argv[k++] = raw_arg;
	}
	return (argv[k] = NULL, argv);
}

int	split_commands(char **argv, t_data *d)
{
	int	arg_index;
	int	cmd_index;
	int	j;

	arg_index = 0;
	cmd_index = 0;
	d->cmd = malloc(sizeof(t_cmd) * d->nb_cmd);
	if (!d->cmd)
		return (ERROR);
	while (cmd_index < d->nb_cmd)
	{
		j = 0;
		d->cmd[cmd_index].nb_arg = count_arg(argv, arg_index);
		d->cmd[cmd_index].arg = malloc(sizeof(char *)
				* (d->cmd[cmd_index].nb_arg + 1));
		if (!d->cmd[cmd_index].arg)
			return (ERROR);
		while (argv[arg_index] && ft_strncmp(argv[arg_index], "|", 2) != 0)
			d->cmd[cmd_index].arg[j++] = ft_strdup(argv[arg_index++]);
		d->cmd[cmd_index].arg[j] = NULL;
		if (argv[arg_index] && ft_strncmp(argv[arg_index], "|", 2) == 0)
			arg_index++;
		cmd_index++;
	}
	return (free_split(argv), SUCCESS);
}

char	**split(t_data *d)
{
	char	**argv;
	int		is_dquote;

	argv = malloc(sizeof(char *) * (ft_strlen(d->input) + 1));
	if (!argv)
		return (NULL);
	is_dquote = 0;
	argv = get_args(d->input, d, &is_dquote, argv);
	if (!argv)
		return (NULL);
	return (argv);
}
