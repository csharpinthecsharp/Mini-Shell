/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:02:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 14:15:08 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void print_error(const char *str, const char *arg)
{
    size_t len_str = ft_strlen(str);
    size_t len_arg = ft_strlen(arg);

    write(STDERR_FILENO, "minishell: ", 11);
    if (arg[0] != '!')
    {
        write(STDERR_FILENO, arg, len_arg);
        write(STDERR_FILENO, " : ", 3);
    }
    write(STDERR_FILENO, str, len_str);
    write(STDERR_FILENO, "\n", 1);
}