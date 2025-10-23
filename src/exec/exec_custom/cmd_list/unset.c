/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:17:48 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/17 17:11:44 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	handle_unset(char **argv, int count, t_data *d)
{
	int	pos;
	int	i;
	int	len;
	int	j;

	if (count == 1)
		return (0);
	pos = 1;
	while (pos < count)
	{
		i = 0;
		while (d->envp[i])
		{
			len = ft_strlen(argv[pos]);
			if (ft_strncmp(argv[pos], d->envp[i], len) == 0
				&& d->envp[i][len] == '=')
			{
				free(d->envp[i]);
				j = i;
				while (d->envp[j + 1])
				{
					d->envp[j] = d->envp[j + 1];
					j++;
				}
				d->envp[j] = NULL;
				break ;
			}
			i++;
		}
		pos++;
	}
	return (0);
}
