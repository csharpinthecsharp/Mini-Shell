/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:20:39 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 00:12:14 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/template.h"

int ft_countword(char **spli_args)
{
    int i = 0;
    while (*spli_args[i])
        i++;
    return (i);
}

char *getpath(char *buffer)
{    
    // On choppe le path.
    // Si -> Erreur <- NULL.
    if (!getcwd(buffer, BUFFER_SIZE))
        return (NULL);
    // On duplique buffer avant de l'envoyer,
    // Il faut lui alouer la mémoire.
    return (ft_strdup(buffer));
}

void print_error(char *str_sub, char *str_cont)
{
    printf(ERROR_PREFIX "%s%s\n" RESET, str_sub, str_cont);
}