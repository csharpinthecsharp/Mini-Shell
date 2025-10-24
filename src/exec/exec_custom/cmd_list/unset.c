/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:17:48 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/24 14:49:47 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static void loop_to_unset(t_data *d, char *argv_tgr_ptr)
{
	int i;
	int j;
	int len;
	
	i = 0;
	j = 0;
	len = 0;
	while (d->envp[i])
	{
		len = ft_strlen(argv_tgr_ptr);
		if (ft_strncmp(argv_tgr_ptr, d->envp[i], len) == 0
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
}

int	handle_unset(char **argv, int count, t_data *d)
{
	int	pos;

	if (count == 1)
		return (SUCCESS);
	pos = 1;
	while (pos < count)
	{
		loop_to_unset(d, argv[pos]);
		pos++;
	}
	return (SUCCESS);
}
