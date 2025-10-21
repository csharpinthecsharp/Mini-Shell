/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:02:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 01:19:19 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	print_error(const char *str, const char *arg)
{
	size_t	len_str;
	size_t	len_arg;

	len_str = ft_strlen(str);
	len_arg = ft_strlen(arg);
	write(STDERR_FILENO, "minishell: ", 11);
	if (arg[0] != '!')
	{
		write(STDERR_FILENO, arg, len_arg);
		write(STDERR_FILENO, " : ", 3);
	}
	write(STDERR_FILENO, str, len_str);
	write(STDERR_FILENO, "\n", 1);
}

void execve_error(char *cmd)
{
    if (errno == ENOENT)
        print_error("Command or file not found", cmd);
    else if (errno == EACCES)
        print_error("Permission denied", cmd);
    else if (errno == ENOMEM)
        print_error("Not enough memory", cmd);
    else if (errno == EFAULT)
        print_error("Invalid pointer", cmd);
    else if (errno == EINVAL)
        print_error("Invalid argument", cmd);
    else if (errno == ENOTDIR)
        print_error("A path component is not a directory", cmd);
    else
        print_error("Execution failed", cmd);
}