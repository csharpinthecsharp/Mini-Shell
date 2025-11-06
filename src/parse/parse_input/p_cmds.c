/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/06 16:36:32 by ltrillar         ###   ########.fr       */
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
	if (!clean)
		return (NULL);
	j = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
			clean[j++] = ft_strdup(tokens[i]);
		free(tokens[i]);
		i++;
	}
	clean[j] = NULL;
	free(tokens);
	return (clean);
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
			arg = expand_arg(raw_arg, d, is_dquote);
		else
			arg = raw_arg;
		if (!arg)
			break ;
		argv[k++] = arg;
	}
	return (argv[k] = NULL, argv);
}

char	*expand_arg(char *raw_arg, t_data *d, int *is_dquote)
{
	char	*arg;
	int		size;

	size = get_expanded_size(raw_arg, d, *is_dquote);
	if (size < 0)
	{
		free(raw_arg);
		return (NULL);
	}
	arg = malloc(size + 3);
	if (!arg)
	{
		free(raw_arg);
		return (NULL);
	}
	arg = replace_envvar(raw_arg, d, is_dquote, arg);
	if (!arg)
	{
		free(raw_arg);
		return (NULL);
	}
	free(raw_arg);
	return (arg);
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
		return (FAILED);
	while (cmd_index < d->nb_cmd)
	{
		j = 0;
		d->cmd[cmd_index].nb_arg = count_arg(argv, arg_index);
		d->cmd[cmd_index].arg = malloc(sizeof(char *)
				* (d->cmd[cmd_index].nb_arg + 1));
		if (!d->cmd[cmd_index].arg)
			return (FAILED);
		while (argv[arg_index] && ft_strncmp(argv[arg_index], "|", 2) != 0)
			d->cmd[cmd_index].arg[j++] = ft_strdup(argv[arg_index++]);
		d->cmd[cmd_index].arg[j] = NULL;
		if (argv[arg_index] && ft_strncmp(argv[arg_index], "|", 2) == 0)
			arg_index++;
		cmd_index++;
	}
	return (SUCCESS);
}

int	split(t_data *d)
{
	char	**argv;
	int		is_dquote;

	argv = malloc(sizeof(char *) * (ft_strlen(d->input) + 1));
	if (!argv)
		return (FAILED);
	is_dquote = 0;
	argv = get_args(d->input, d, &is_dquote, argv);
	d->nb_cmd = count_commands(argv);
	if (split_commands(argv, d) == FAILED)
		return (FAILED);
	free_split(argv);
	return (SUCCESS);
}
