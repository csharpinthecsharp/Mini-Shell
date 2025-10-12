/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:20:39 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/12 16:01:02 by ltrillar         ###   ########.fr       */
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

char *getpath(char *buffer, t_data *d)
{    
    // On choppe le path.
    // Si -> Erreur <- NULL.

    if (!getcwd(buffer, 1024))
        return (NULL);
    // On duplique buffer avant de l'envoyer,
    // Il faut lui alouer la mémoire.
    if (d->new_path == NULL)
        return (ft_strdup(buffer));
    return (ft_strjoin(buffer, d->new_path));
}

char *get_promptpath(char *buffer, t_data *d)
{
    (void)buffer;
    (void)d;

    char *prompt = ft_strjoin(TEMPLATE_PROMPT, "vbash");
    if (!prompt)
        return (NULL);

    char *full_prompt = ft_strjoin(prompt, TEMPLATE_PROMPT_END);
    free(prompt);

    return full_prompt;
}

void print_error(const char *str, const char *arg)
{
    size_t len_str = ft_strlen(str);
    size_t len_arg = ft_strlen(arg);

    write(STDERR_FILENO, "minishell: ", 11);
    if (arg[0] != '!')
    {
        write(STDERR_FILENO, arg, len_arg);
        write(STDERR_FILENO, " : ", 3);
    }
    write(STDERR_FILENO, str, len_str);
    write(STDERR_FILENO, "\n", 1);
}

int ft_isspace(char arg)
{
    if (arg == ' ' || arg == '\t')
        return (1);
    return (0);
}


