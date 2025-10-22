/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:37:54 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 23:59:31 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int handle_exit(t_data *d, char **argv, int count)
{
    (void)d;
    (void)count;
    long status;
    if (!argv[1])
        exit(EXIT_SUCCESS);

    if (!(is_numeric(argv[1], 0)))
    {
        print_error("numeric argument required", argv[1]);
        exit(2);
    }

    if (argv[2])
    {
        print_error("too many arguments", argv[0]);
        return (FAILED);
    }
    
    status = ft_atoi(argv[1]);
    printf("exit\n");
    exit((unsigned char)status);
}
