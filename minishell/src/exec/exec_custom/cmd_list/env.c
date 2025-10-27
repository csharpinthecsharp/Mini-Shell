/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrezette <lrezette@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:39:38 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/27 21:42:44 by lrezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*ft_get_env(t_data *d, char *requested)
{
	int	i;
	int	len;

	if (!d || !d->envp || !requested)
		return (NULL);
	len = ft_strlen(requested);
	if (len == 0)
		return (NULL);
	i = 0;
	while (d->envp[i])
	{
		if (ft_strncmp(d->envp[i], requested, len) == 0
			&& d->envp[i][len] == '=')
		{
			return (d->envp[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

int	handle_env(char **argv, int count, t_data *d)
{
	int	i;

	(void)argv;
	if (count == 1)
	{
		i = 0;
		while (d->envp[i])
		{
			printf("%s\n", d->envp[i]);
			i++;
		}
	}
	return (SUCCESS);
}
