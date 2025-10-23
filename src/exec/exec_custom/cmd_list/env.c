/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:39:38 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 16:04:26 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*ft_get_env(t_data *d, char *requested)
{
	int	i;

	i = 0;
	while (d->envp[i])
	{
		if (ft_strncmp(d->envp[i], requested, ft_strlen(requested)) == 0
			&& d->envp[i][ft_strlen(requested)] == '=')
		{
			return (d->envp[i] + ft_strlen(requested) + 1);
		}
		i++;
	}
	return (NULL);
}

int	handle_env(char **argv, int count, t_data *d)
{
	(void)argv;
	if (count == 1)
	{
		int i = 0;
		while (d->envp[i])
		{
			printf("%s\n", d->envp[i]);
			i++;
		}
	}
	return (0);
}