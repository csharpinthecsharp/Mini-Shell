/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 14:02:56 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**remove_empty_var(char **tokens)
{
	int		count;
	char	**clean;
	int		i;
    int j;

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

char	**get_args(char *s, t_data *d)
{
	int		i;
	int		k;
	int		is_dquote;
	int		len;
	char	**argv;
	char	*raw_arg;
	char	*arg;

	i = 0;
	k = 0;
	is_dquote = 0;
	len = ft_strlen(s);
	argv = malloc(sizeof(char *) * (len + 1));
	if (!argv)
		return (NULL);
	while (s[i])
	{
		raw_arg = get_one_arg(s, &i, &is_dquote);
		if (!raw_arg)
			break ;
		if (ft_strchr(raw_arg, '$'))
		{
			arg = replace_envvar(raw_arg, d, &is_dquote);
			argv[k++] = arg;
			free(raw_arg);
		}
		else
			argv[k++] = raw_arg;
	}
	argv[k] = NULL;
	return (argv);
}

int	split_commands(char **argv, t_data *d)
{
	int	arg_index;
	int	cmd_index;
	int	j;

	arg_index = 0;
	cmd_index = 0;
	d->nb_cmd = count_commands(argv);
	d->cmd = malloc(sizeof(t_cmd) * d->nb_cmd);
	if (!d->cmd)
		return (-1);
	while (cmd_index < d->nb_cmd)
	{
		j = 0;
		d->cmd[cmd_index].nb_arg = count_arg(argv, arg_index);
		d->cmd[cmd_index].arg = malloc(sizeof(char *)
				* (d->cmd[cmd_index].nb_arg + 1));
		if (!d->cmd[cmd_index].arg)
			return (-1);
		while (argv[arg_index] && ft_strncmp(argv[arg_index], "|", 2) != 0)
			d->cmd[cmd_index].arg[j++] = ft_strdup(argv[arg_index++]);
		d->cmd[cmd_index].arg[j] = NULL;
		if (argv[arg_index] && ft_strncmp(argv[arg_index], "|", 2) == 0)
			arg_index++;
		cmd_index++;
	}
	if (argv)
		free_split(argv);
	return (SUCCESS);
}

char	**split(t_data *d)
{
	char	**argv;

	argv = get_args(d->input, d);
	if (!argv)
		return (NULL);
	return (argv);
}
