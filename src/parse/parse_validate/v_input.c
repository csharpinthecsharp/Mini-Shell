/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:46:28 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 01:30:25 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	handle_quote_state(char *input, int *pos, char *quote)
{
	if (*quote == 0 && (input[*pos] == '\'' || input[*pos] == '"'))
	{
		*quote = input[*pos];
		(*pos)++;
		return (SUCCESS);
	}
	if (input[*pos] == *quote)
	{
		*quote = 0;
		(*pos)++;
		return (SUCCESS);
	}
	if (*quote)
	{
		(*pos)++;
		return (SUCCESS);
	}
	return (-1);
}

int	redirection_syntax(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (check_in_check_redir(input, &i, &quote) == FAILED)
			return (FAILED);
	}
	if (quote)
	{
		print_error("syntax error: unmatched quote", "!");
		return (FAILED);
	}
	return (SUCCESS);
}

int	pipe_syntax(char *input)
{
	int		i;
	char	quote;
	int		res;

	i = 0;
	quote = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
	{
		print_error("syntax error near unexpected token `|'", "!");
		return (FAILED);
	}
	while (input[i])
	{
		if (handle_quote_state(input, &i, &quote) == SUCCESS)
			continue ;
		res = check_in_check_pipe(input, &quote, &i);
		if (res == FAILED)
			return (FAILED);
		else if (res == 2)
			continue ;
		i++;
	}
	return (SUCCESS);
}
