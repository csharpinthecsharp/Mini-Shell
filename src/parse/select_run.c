/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:57:15 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 16:35:03 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_command(char **argv)
{
    // return 0 = on a pas trouvé de commande dedans.
    // return 1 = on a trouvé une commande qu'il faut build.
    // return 2 = pas besoin de la build, juste execve.
    int len = ft_strlen(argv[0]);
    if (ft_strncmp(argv[0], "pwd", len) == 0)
        return (1);
    else if (ft_strncmp(argv[0], "exit", len) == 0)
        return (1);
    else if (ft_strncmp(argv[0], "echo", len) == 0)
        return (1);
    else if (ft_strncmp(argv[0], "cd", len) == 0)
        return (1);
    else if (ft_strncmp(argv[0], "export", len) == 0)
        return (1);
    return (0);
}
