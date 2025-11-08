/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:37:19 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/08 12:52:56 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	handle_pwd(char *argv, int count, char *path, t_data *d)
{
	(void)count;
	(void)argv;
	(void)path;
	printf("%s\n", ft_get_env(d, "PWD"));
	return (0);
}
