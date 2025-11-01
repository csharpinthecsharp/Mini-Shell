/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:39:16 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/01 17:39:56 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 1;
	while (!str || !str[0])
		return (0);
	while (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (FAILED);
}

static int	loop_in_env(int *index, t_data *d, char *key, char **arg_ptr)
{
	(*index) = 0;
	while (d->envp[*index])
	{
		if (ft_strncmp(d->envp[*index], key, ft_strlen(key)) == 0
			&& d->envp[*index][ft_strlen(key)] == '=')
		{
			free(d->envp[*index]);
			d->envp[*index] = ft_strdup(*arg_ptr);
			return (SUCCESS);
		}
		(*index)++;
	}
	(*index) = 0;
	while (d->envp[*index])
		(*index)++;
	return (FAILED);
}

static int	do_export(char **argv, t_data *d)
{
	char	*arg;
	int		len;
	char	*key;
	char	**new_envp;
	int		index;
	arg = argv[1];
	if (error_export(ft_strchr(arg, '='), &arg) == FAILED)
		return (FAILED);
	len = ft_strchr(arg, '=') - arg;
	key = malloc(len + 1);
	if (!key)
		return (FAILED);
	ft_strlcpy(key, arg, len + 1);
	if (loop_in_env(&index, d, key, &arg) == SUCCESS)
	{
		free(key);
		return (SUCCESS);
	}
	new_envp = ft_realloc(d->envp, sizeof(char *) * (index),
			sizeof(char *) * (index + 2));
	if (!new_envp)
	{
		free(key);
		return (FAILED);
	}
	d->envp = new_envp;
	d->envp[index] = ft_strdup(arg);
	d->envp[index + 1] = NULL;
	free(key);
	return (SUCCESS);
}


int	handle_export(char **argv, int count, t_data *d)
{
	int	i;

	i = 0;
	if (count == 1)
	{
		while (d->envp[i])
		{
			printf("%s\n", d->envp[i]);
			i++;
		}
		return (0);
	}
	if (count == 2)
	{
		if (do_export(argv, d) == FAILED)
			return (FAILED);
	}
	return (SUCCESS);
}
