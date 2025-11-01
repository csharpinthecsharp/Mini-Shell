/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_args.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:34:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/27 20:01:44 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	skip_quoted(const char *s, int *i, char quote_char)
{
	(*i)++;
	while (s[*i] && s[*i] != quote_char)
		(*i)++;
	(*i)++;
}

static void	handle_quote(const char *s, int *i, int *is_dquote)
{
	while (s[*i] && !ft_isspace(s[*i]) && s[*i] != '|' && s[*i] != '<'
		&& s[*i] != '>')
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			if (s[*i] == '\'')
				(*is_dquote) = 1;
			skip_quoted(s, i, s[*i]);
		}
		else
			(*i)++;
	}
}

int	get_arg_length(const char *s, int *i, int *is_dquote)
{
	int	start;

	start = *i;
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	if (!s[*i])
		return (0);
	if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
	{
		if (s[*i + 1] == '<' && s[*i] == '<')
			(*i) += 2;
		else if (s[*i + 1] == '>' && s[*i] == '>')
			(*i) += 2;
		else
			(*i) += 1;
		return (1);
	}
	handle_quote(s, i, is_dquote);
	return (*i - start);
}

static void	loop_into_arg(const char *s, int end, int *k, char **dst)
{
	char	qc;

	if (s[*k] == '\'' || s[*k] == '"')
	{
		qc = s[(*k)++];
		while (*k < end && s[*k] != qc)
			*(*dst)++ = s[(*k)++];
		if (*k < end && s[*k] == qc)
			(*k)++;
	}
	else
	{
		if (ft_isspace((unsigned char)s[*k]))
			(*k)++;
		else
			*(*dst)++ = s[(*k)++];
	}
}

char	*get_one_arg(char *s, int *i, int *is_dquote)
{
	int		start;
	int		len;
	char	*arg;
	char	*dst;
	int		k;

	start = *i;
	len = get_arg_length(s, i, is_dquote);
	if (len <= 0)
		return (NULL);
	arg = malloc((size_t)len + 1);
	if (!arg)
		return (NULL);
	dst = arg;
	k = start;
	while (k < *i)
		loop_into_arg(s, *i, &k, &dst);
	*dst = '\0';
	return (arg);
}
