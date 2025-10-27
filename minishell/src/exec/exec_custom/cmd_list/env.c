/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:39:38 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/27 17:06:59 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*ft_get_env(t_data *d, char *requested)
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen(requested);
	while (d->envp[i])
	{
		if (ft_strncmp(d->envp[i], requested, ft_strlen(requested)) == 0
			&& d->envp[i][ft_strlen(requested)] == '=')
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
