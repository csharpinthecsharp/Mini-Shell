/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:12:44 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/28 15:32:19 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *getpath(char *buffer)
{    
    // On choppe le path.
    // Si -> Erreur <- NULL.
    if (!getcwd(buffer, BUFFER_SIZE))
        return (NULL);
    
    int buff_len = ft_strlen(buffer);
    
    // Là on copie "\n" dans le buffer.
    ft_strlcat(buffer, "\n", buff_len + 2);

    // On duplique buffer avant de l'envoyer,
    // Il faut lui alouer la mémoire.
    return (ft_strdup(buffer));
}