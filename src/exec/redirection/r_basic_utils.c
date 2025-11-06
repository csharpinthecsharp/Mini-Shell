/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_basic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:49:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 14:00:40 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	is_heredoc_delimiter_quoted(char *input, char *parsed_delimiter)
{
	size_t	len;
	int		i;

	len = ft_strlen(parsed_delimiter);
	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i] && ft_isspace(input[i]))
				i++;
			if (input[i] == '\'' || input[i] == '"')
				return (1);
			if (!ft_strncmp(&input[i], parsed_delimiter, len))
				return (0);
		}
		i++;
	}
	return (0);
}

static int	get_redirection_type(char *token)
{
	if (!token)
		return (-1);
	if (!ft_strncmp(token, ">>", 3))
		return (RIGHT_RIGHT);
	if (!ft_strncmp(token, ">", 2))
		return (RIGHT);
	if (!ft_strncmp(token, "<<", 3))
		return (LEFT_LEFT);
	if (!ft_strncmp(token, "<", 2))
		return (LEFT);
	return (-1);
}

static bool	assign_redirection(t_arguments *redir, int type, char *file)
{
	redir->state_redir = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
		return (false);
	redir->heredoc_quoted = 0;
	return (true);
}

bool	put_redir(t_data *d, int cmd_index, int arg_index, int redir_index)
{
	int			type;
	char		*file;
	t_arguments	*redir;

	type = get_redirection_type(d->cmd[cmd_index].arg[arg_index]);
	file = d->cmd[cmd_index].arg[arg_index + 1];
	if (type == -1 || !file)
		return (false);
	redir = &d->cmd[cmd_index].arguments[redir_index];
	if (!assign_redirection(redir, type, file))
		return (false);
	if (type == LEFT_LEFT)
		redir->heredoc_quoted = is_heredoc_delimiter_quoted(d->input, file);
	return (true);
}
