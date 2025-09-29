/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:17:48 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/29 15:06:25 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_pwd(char *argv, int count, char *path)
{
    if (count != 1)
    {
        print_error(argv, ": too many arguments");
        return (0);
    }
    printf("%s\n", path);
    return (0);
}