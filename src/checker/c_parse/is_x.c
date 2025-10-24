/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 01:22:52 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/24 13:55:01 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_numeric(const char *str, int strict)
{
	int	i;

	if (!str || !str[0])
		return (SUCCESS);
	i = 0;
	if (!strict && (str[0] == '+' || str[0] == '-'))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (SUCCESS);
		i++;
	}
	return (FAILED);
}

int	isfulls(char *s)
{
	size_t	i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (ft_strlen(s) == i)
		return (FAILED);
	else
		return (SUCCESS);
}