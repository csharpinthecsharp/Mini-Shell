/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_envvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:32:50 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/06 17:03:52 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	get_expanded_size(char *s, t_data *d, int is_dquote)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (is_key_exitstatus(s, is_dquote) == SUCCESS)
		{
			if (expand_exit_status(d, &len) == ERROR)
				return (ERROR);
			s += 2;
			continue ;
		}
		if (*s == '$' && is_dquote == 0)
		{
			s++;
			h_expand_size(&s, &len, d);
			continue ;
		}
		len++;
		s++;
	}
	return (len);
}

char	*get_env_string(t_data *d, char *s)
{
	int		i;
	int		j;
	char	*arg;
	char	*env_val;

	i = 0;
	j = 0;
	arg = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!arg)
		return (NULL);
	if (s[i] == '$')
		i++;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '$' && s[i] != '('
		&& s[i] != ')')
		arg[j++] = s[i++];
	arg[j] = '\0';
	if (j == 0)
		return (free(arg), ft_strdup(""));
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

int	handle_expansion(char *s, t_data *d, char **arg, int *indices)
{
	char	*ptr;

	if (is_key_exitstatus(s + indices[0], indices[2]) == SUCCESS)
	{
		if (repl_exitstatus(d, &indices[0], arg, &indices[1]) == FAILED)
			return (FAILED);
	}
	else if (s[indices[0]] == '$' && indices[2] == 0)
	{
		ptr = s + indices[0];
		if (process_dollar(&ptr, d, arg, &indices[1]) == FAILED)
			return (FAILED);
		indices[0] = (int)(ptr - s);
	}
	else
		(*arg)[indices[1]++] = s[indices[0]++];
	return (SUCCESS);
}
