/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_utility.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 01:02:00 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/27 20:09:35 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	count_commands(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "|", 2) == 0)
			count++;
		i++;
	}
	return (count + 1);
}

int	count_arg(char **argv, int i)
{
	int	count;

	count = 0;
	while (argv[i] && ft_strncmp(argv[i], "|", 2) != 0)
	{
		count++;
		i++;
	}
	return (count);
}

int	count_cmds(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i - 1);
}

int	count_redir(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], ">>", 3) || !ft_strncmp(argv[i], ">", 2)
			|| !ft_strncmp(argv[i], "<<", 3) || !ft_strncmp(argv[i], "<", 2))
		{
			count++;
			if (argv[i + 1])
				i++;
		}
		i++;
	}
	return (count);
}
