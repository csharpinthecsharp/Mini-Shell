/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:38:38 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 12:38:44 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int handle_cd(char **argv, int count, t_data *d)
{
    char *target_path;

    if (count == 1)
        target_path = getenv("HOME"); // fallback vers le home
    else if (count == 2)
        target_path = argv[1];
    else
    {
        print_error("too many arguments", argv[0]);
        return FAILED;
    }

    if (chdir(target_path) != 0)
    {
        print_error("No such file or directory", argv[0]);
        return FAILED;
    }

    char *buffer = malloc(sizeof(char) * 1024);
    if (!getcwd(buffer, 1024))
    {
        perror("getcwd failed");
        d->path = ft_strdup("?");
    }
    else
        d->path = ft_strdup(buffer);
    free(buffer);
    return SUCCESS;
}