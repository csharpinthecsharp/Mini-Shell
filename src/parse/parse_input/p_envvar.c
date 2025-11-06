/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_envvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:32:50 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/06 16:36:42 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int expand_exit_status(t_data *d, int *len)
{
	char	*exit_status;
	
	exit_status = ft_itoa(d->exit_status);
	if (!exit_status)
		return (ERROR);
	(*len) += ft_strlen(exit_status);
	free(exit_status);
	return (SUCCESS);
}
int	get_expanded_size(char *s, t_data *d, int is_dquote)
{
	int		len;

	len = 0;
	while (*s)
	{
		if (is_key_exitstatus(s, is_dquote) == SUCCESS)
		{
			if (expand_exit_status(d, &len) == ERROR)
				return (ERROR);
			s += 2;
			continue;
		}
		if (*s == '$' && is_dquote == 0)
		{
			s++;
			h_expand_size(&s, &len, d);
			continue;
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
