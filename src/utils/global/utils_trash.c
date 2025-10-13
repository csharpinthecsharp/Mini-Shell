/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:20:39 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 21:11:00 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/template.h"

int ft_countword(char **spli_args)
{
    int i = 0;
    while (*spli_args[i])
        i++;
    return (i);
}

char *getpath(char *buffer, t_data *d)
{    
    if (!getcwd(buffer, 1024))
        return (NULL);
    if (d->new_path == NULL)
        return (ft_strdup(buffer));
    return (ft_strjoin(buffer, d->new_path));
}

char *get_promptpath(char *buffer, t_data *d)
{
    (void)buffer;
    (void)d;

    char *res = malloc(sizeof(char) * ft_strlen(d->path));
    if (!res)
        return (NULL);
    char *trimmed_path = ft_strdup(d->path);
    int i = ft_strlen(trimmed_path);
    while (trimmed_path[i - 1] != '/')
        i--;
    int j = 0;
    while (trimmed_path[i])
        res[j++] = trimmed_path[i++];
    res[j] = '\0';
    free(trimmed_path);
    char *prompt = ft_strjoin(TEMPLATE_PROMPT, res);
    if (!prompt)
        return (NULL);
    free(res);
    char *full_prompt = ft_strjoin(prompt, TEMPLATE_PROMPT_END);
    free(prompt);

    return (full_prompt);
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

int is_numeric(const char *str)
{
    int i = 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int isfulls(char *s)
{
    size_t i = 0;
    while (ft_isspace(s[i]))
        i++;
    if (ft_strlen(s) == i)
        return (1);
    else
        return (0);
}