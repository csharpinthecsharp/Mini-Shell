/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 01:22:55 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/24 14:01:05 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_in_check_redir(char *input, int *pos, char *quote)
{
	int	type;

	if (handle_quote_state(input, pos, quote) != -1)
		return (SUCCESS);
	if (input[*pos] == '>' || input[*pos] == '<')
	{
		type = input[(*pos)++];
		if (input[*pos] == type)
			(*pos)++;
		while (input[*pos] && input[*pos] == ' ')
			(*pos)++;
		if (!input[*pos])
		{
			print_error("syntax error near unexpected token `newline'", "!");
			return (FAILED);
		}
		if (input[*pos] == '>' || input[*pos] == '<' || input[*pos] == '|')
		{
			print_error("syntax error near unexpected token", "operator");
			return (FAILED);
		}
	}
	else
		(*pos)++;
	return (SUCCESS);
}

int	check_in_check_pipe(char *input, char *quote, int *pos)
{
	int	j;

	if (*quote)
	{
		(*pos)++;
		return (2);
	}
	if (input[(*pos)] == '|' && input[(*pos) + 1] == '|')
	{
		print_error("syntax error near unexpected token `||'", "!");
		return (FAILED);
	}
	if (input[*pos] == '|' && input[(*pos) + 1])
	{
		j = (*pos) + 1;
		while (input[j] == ' ')
			j++;
		if (input[j] == '|')
		{
			print_error("syntax error near unexpected token `|'", "!");
			return (FAILED);
		}
	}
	return (SUCCESS);
}
