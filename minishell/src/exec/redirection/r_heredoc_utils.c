/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_heredoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:10:03 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/01 11:28:01 by astrelci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	restore_terminal_settings(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != -1)
	{
		term.c_lflag |= (ECHO | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

int	heredoc_read_loop(int fd_write, char *delimiter)
{
	char	*res;

	while (1)
	{
		res = readline("> ");
		if (!res)
		{
			print_error("here-document delimited by end-of-file", "warning");
			return (1);
		}
		if (ft_strncmp(res, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(res);
			return (0);
		}
		ft_putstr_fd(res, fd_write);
		ft_putstr_fd("\n", fd_write);
		free(res);
	}
}
