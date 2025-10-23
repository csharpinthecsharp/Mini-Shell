/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:39:16 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/23 19:51:27 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static int	is_valid_identifier(const char *str)
{
	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	for (int i = 1; str[i] && str[i] != '='; i++)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

int	handle_export(char **argv, int count, t_data *d)
{
	int		i;
	char	*arg;
	char	*equal_sign;
	char	*equal;
	int		len;
	char	*key;
	char	**new_envp;

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
		arg = argv[1];
		equal_sign = ft_strchr(arg, '=');
		if (!equal_sign)
		{
			if (!is_valid_identifier(arg))
			{
				print_error("not a valid identifier", arg);
				return (1);
			}
			arg = ft_strjoin(arg, "=''");
		}
		if (arg[0] == '=' || !is_valid_identifier(arg))
		{
			print_error("not a valid identifier", arg);
			return (1);
		}
		equal = ft_strchr(arg, '=');
		len = equal - arg;
		key = malloc(len + 1);
		ft_strlcpy(key, arg, len + 1);
		i = 0;
		while (d->envp[i])
		{
			if (ft_strncmp(d->envp[i], key, ft_strlen(key)) == 0
				&& d->envp[i][ft_strlen(key)] == '=')
			{
				free(d->envp[i]);
				d->envp[i] = ft_strdup(arg);
				return (0);
			}
			i++;
		}
		i = 0;
		while (d->envp[i])
			i++;
		new_envp = realloc(d->envp, sizeof(char *) * (i + 2));
		if (!new_envp)
			return (1);
		d->envp = new_envp;
		d->envp[i] = ft_strdup(arg);
		d->envp[i + 1] = NULL;
	}
	return (0);
}
