/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_envvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:32:50 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/27 19:20:50 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	get_expanded_size(char *s, t_data *d)
{
	int		len;
	char	*val;

	len = 0;
	while (*s)
	{
		if (*s == '$')
		{
			s++;
			if (*s && !ft_isspace((unsigned char)*s))
			{
				val = get_env_string(d, s);
				if (!val)
					return (0);
				while (*s && !ft_isspace((unsigned char)*s) && *s != '$')
					s++;
				len += ft_strlen(val);
				free(val);
				continue ;
			}
		}
		len++;
		s++;
	}
	return (len);
}

char	*get_env_string(t_data *d, char *s)
{
	int		i = 0;
	int		j = 0;
	char	*arg;
	char	*env_val;

	arg = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!arg)
		return (NULL);
	if (s[i] == '$')
		i++;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '$' && s[i] != '(' && s[i] != ')')
		arg[j++] = s[i++];
	arg[j] = '\0';
	if (j == 0)
	{
		free(arg);
		return (ft_strdup(""));
	}
	env_val = ft_get_env(d, arg);
	free(arg);
	if (!env_val)
		return (ft_strdup(""));
	return (ft_strdup(env_val));
}


static int	process_dollar(char **ps, t_data *d, char **arg, int *j)
{
	char	*s;
	char	*val;
	int		k;

	s = *ps;
	if (!s[1] || ft_isspace((unsigned char)s[1]))
	{
		(*arg)[(*j)++] = *s;
		(*ps) = s + 1;
		return (SUCCESS);
	}
	val = get_env_string(d, s);
	if (!val)
		return (FAILED);
	s++;
	while (*s && !ft_isspace((unsigned char)*s) && *s != '$')
		s++;
	k = 0;
	while (val[k])
		(*arg)[(*j)++] = val[k++];
	free(val);
	*ps = s;
	return (SUCCESS);
}

static int	repl_exitstatus(t_data *d, int *i, char **arg, int *j)
{
	char	*envv;
	int		k;

	envv = ft_itoa(d->exit_status);
	if (!envv)
		return (FAILED);
	k = 0;
	while (envv[k])
		(*arg)[(*j)++] = envv[k++];
	free(envv);
	(*i) += 2;
	return (SUCCESS);
}

char	*replace_envvar(char *s, t_data *d, int *is_dquote, char *arg)
{
	int		i;
	int		j;
	char	*ptr;

	if (!s)
		return (ft_strdup(""));
	i = 0;
	j = 0;
	while (s[i])
	{
		if ((is_key_exitstatus(s + i, *is_dquote) == SUCCESS)
			&& (repl_exitstatus(d, &i, &arg, &j) == FAILED))
			return (free(arg), NULL);
		else if (s[i] == '$' && *is_dquote == 0)
		{
			ptr = s + i;
			if (process_dollar(&ptr, d, &arg, &j) == FAILED)
				return (free(arg), NULL);
			i = (int)(ptr - s);
		}
		else
			arg[j++] = s[i++];
	}
	return (arg[j] = '\0', arg);
}
