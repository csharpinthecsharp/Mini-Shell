/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:59:03 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 23:36:21 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*up_shlvl(char *envp_i)
{
	int		lvl;
	char	*new_lvl;
	char	*res;

	if (ft_strncmp(envp_i, "SHLVL=", 6) == 0)
	{
		lvl = ft_atoi(envp_i + 6);
		lvl++;
		new_lvl = ft_itoa(lvl);
		res = ft_strjoin("SHLVL=", new_lvl);
		free(new_lvl);
		return (res);
	}
	return (ft_strdup(envp_i));
}

char	**duplicate_envp(char **envp)
{
	int		count;
	char	**argv;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		argv[i] = up_shlvl(envp[i]);
		if (!argv[i])
		{
			while (i > 0)
				free(argv[--i]);
			free(argv);
			return (NULL);
		}
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
