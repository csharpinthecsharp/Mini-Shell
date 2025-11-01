/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:59:03 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/31 20:51:13 by astrelci         ###   ########.fr       */
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
		if (!new_lvl)
			return (ft_strdup(envp_i));
		res = ft_strjoin("SHLVL=", new_lvl);
		free(new_lvl);
		return (res);
	}
	return (ft_strdup(envp_i));
}

char	**duplicate_envp(char **envp)
{
	int		count;
	int		i;
	char	**copy;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = up_shlvl(envp[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
