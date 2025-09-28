/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:12:44 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/28 14:05:12 by ltrillar         ###   ########.fr       */
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
    
    // Là on copie ": " dans le buffer.
    ft_strlcat(buffer, ": ", buff_len + 3);

    // On duplique buffer avant de l'envoyer,
    // Il faut lui alouer la mémoire.
    return (ft_strdup(buffer));
}

pid_t get_from_path(char *buffer, char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (-1);
    
    int index = 0;
    int bytes_read = 0;
    char current;
    
    while ((bytes_read = read(fd, &current, 1)) > 0)
        buffer[index++] = current;
        
    if (bytes_read < 0)
        return (-1);

    return (ft_atoi(buffer));
}