/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:37:54 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 12:38:05 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int handle_exit(char **argv, int count)
{
    (void)count;
    if (!argv[1])
        exit(0);

    if (!is_numeric(argv[1]))
    {
        print_error("numeric argument required", argv[1]);
        exit(2);
    }

    if (argv[2])
    {
        print_error("too many arguments", argv[0]);
        return 1;
    }

    exit(ft_atoi(argv[1]) % 256);
}