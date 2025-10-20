/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:20:39 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/20 17:22:12 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_countword(char **spli_args)
{
	int	i;

	i = 0;
	while (*spli_args[i])
		i++;
	return (i);
}

int	ft_isspace(char arg)
{
	if (arg == ' ' || arg == '\t')
		return (1);
	return (0);
}

int	is_numeric(const char *str, int strict)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (!strict && (str[0] == '+' || str[0] == '-'))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	isfulls(char *s)
{
	size_t	i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (ft_strlen(s) == i)
		return (1);
	else
		return (0);
}
