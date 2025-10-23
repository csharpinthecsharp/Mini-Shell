/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:37:19 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 17:34:21 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	handle_pwd(char *argv, int count, char *path)
{
	(void)count;
	(void)argv;
	printf("%s\n", path);
	return (0);
}
