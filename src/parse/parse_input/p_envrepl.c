/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_envrepl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:32:50 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/08 12:12:07 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*replace_envvar(char *s, t_data *d, int *is_dquote, char *arg)
{
	int	indices[3];

	if (!s)
		return (ft_strdup(""));
	indices[0] = 0;
	indices[1] = 0;
	indices[2] = *is_dquote;
	while (s[indices[0]])
		if (handle_expansion(s, d, &arg, indices) == FAILED)
			return (free(arg), NULL);
	return (arg[indices[1]] = '\0', arg);
}
