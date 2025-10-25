/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_helper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:32:50 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 15:08:23 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*get_env_string(t_data *d, char *s)
{
	int		i;
	int		j;
	char	*arg;
	int		env_index;

	arg = malloc(sizeof(char) * 256);
	if (handle_error_malloc(arg) == FAILED)
		return (NULL);
	i = 0;
	j = 0;
	if (s[i] == '$')
		i++;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '$')
		arg[j++] = s[i++];
	arg[j] = '\0';
	env_index = 0;
	while (d->envp[env_index])
	{
		if (ft_strncmp(d->envp[env_index], arg, ft_strlen(arg)) == 0
			&& d->envp[env_index][ft_strlen(arg)] == '=')
		{
			return (ft_strdup(ft_get_env(d, arg)));
		}
		env_index++;
	}
	free(arg);
	return (ft_strdup(""));
}

char	*replace_envvar(char *s, t_data *d, int *is_dquote)
{
	int		i;
	int		j;
	int		k;
	int		env_len;
	char	*envvar;
	char	*arg;
	char	*env_value;

	envvar = ft_itoa(d->exit_status);
	if (handle_error_malloc(envvar) == FAILED)
		return (NULL);
	arg = malloc(sizeof(char) * ft_strlen(s) + ft_strlen(envvar) + 256);
	if (handle_error_malloc(arg) == FAILED)
		return (NULL);
	i = 0;
	j = 0;
	(void)env_len;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?' && *is_dquote == 0)
		{
			k = 0;
			while (envvar[k])
				arg[j++] = envvar[k++];
			i += 2;
		}
		else if (s[i] == '$' && *is_dquote == 0)
		{
			if (s[i + 1] == '\0' || ft_isspace(s[i + 1]))
			{
				arg[j++] = s[i++];
				continue ;
			}
			env_value = get_env_string(d, s + i);
			if (!env_value)
				return (free(envvar), NULL);
			i++;
			while (s[i] && !ft_isspace(s[i]) && s[i] != '$')
				i++;
			k = 0;
			while (env_value[k])
				arg[j++] = env_value[k++];
			free(env_value);
		}
		else
		{
			arg[j++] = s[i++];
		}
	}
	arg[j] = '\0';
	return (free(envvar), arg);
}
