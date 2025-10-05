/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:20:39 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 20:38:14 by ltrillar         ###   ########.fr       */
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

char *get_promptpath(char *buffer)
{
    if (!getcwd(buffer, BUFFER_SIZE))
        return (NULL);
    char tmp[BUFFER_SIZE];
    int i = 0;
    while (buffer[i])
        i++;
    buffer[i] = '\0';
    
    while (i--)
    {
        if (buffer[i - 1] == '/')
            break;
    }
    
    int j = 0;
    while (buffer[i])
        tmp[j++] = buffer[i++];
        
    tmp[j] = '\0';
    
    char *t = ft_strdup(ft_strjoin(TEMPLATE_PROMPT, tmp));
    char *t2 = ft_strdup(ft_strjoin(t, TEMPLATE_PROMPT_END));
    return (ft_strdup(t2));
}

void print_error(char *str_sub, char *str_cont)
{
    printf(ERROR_PREFIX "%s%s\n" RESET, str_sub, str_cont);
}

int ft_isspace(char arg)
{
    if (arg == ' ' || arg == '\t')
        return (1);
    return (0);
}

int pipe_count(char **argv)
{
    int i = 0;
    int count = 0;
    while (argv[i])
    {
        int j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] == PIPE)
                count++;
            j++;
        }
        i++;
    }
    return (count);
}
