/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:20:39 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 20:09:08 by ltrillar         ###   ########.fr       */
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
        return NULL;

    char *tmp = malloc(sizeof(char) * BUFFER_SIZE);
    if (!tmp)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (buffer[i])
        i++;

    while (i > 0)
    {
        if (buffer[i - 1] == '/')
            break;
        i--;
    }

    int j = 0;
    while (buffer[i])
        tmp[j++] = buffer[i++];
    tmp[j] = '\0';

    char *t = ft_strjoin(TEMPLATE_PROMPT, tmp);
    char *t2 = ft_strjoin(t, TEMPLATE_PROMPT_END);
    free(t);
    free(tmp);
    return t2;
}


void print_error(const char *str, const char *arg)
{
    size_t len_str = ft_strlen(str);
    size_t len_arg = ft_strlen(arg);
    write(STDERR_FILENO, "minishell: exit: ", 17);
    write(STDERR_FILENO, arg, len_arg);
    write(STDERR_FILENO, " : ", 3);
    write(STDERR_FILENO, str, len_str);
    write(STDERR_FILENO, "\n", 1);
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
