/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:20:39 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/31 16:32:34 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_countword(char **spli_args)
{
	int	i;

	i = 0;
	while (*spli_args[i])
		i++;
	return (i);
}

int	ft_isspace(char arg)
{
	if (arg == ' ' || arg == '\t')
		return (1);
	return (0);
}

void	h_expand_size(char **s, int *len, t_data *d)
{
	char	*val;
	char	*start;

	if (!**s || ft_isspace((unsigned char)**s))
	{
		(*len)++;
		return ;
	}
	start = *s;
	while (**s && !ft_isspace((unsigned char)**s) && **s != '$')
		(*s)++;
	val = get_env_string(d, start - 1);
	if (val)
	{
		*len += ft_strlen(val);
		free(val);
	}
}

char	*expand_arg(char *raw_arg, t_data *d, int *is_dquote)
{
	char	*arg;
	int		size;

	size = get_expanded_size(raw_arg, d);
	arg = malloc(size + 1);
	if (!arg)
		return (NULL);
	arg = replace_envvar(raw_arg, d, is_dquote, arg);
	if (!arg || break_free(arg, raw_arg) == FAILED)
		return (NULL);
	return (arg);
}
