/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:34:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 20:08:58 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Avance jusqu'à la fin d'un segment entre quotes simples ou doubles
// Retourne -1 si quote non fermée
static int skip_quoted(const char *s, int *i, char quote_char)
{
    (*i)++; // skip ouverture
    while (s[*i] && s[*i] != quote_char)
        (*i)++;
    if (!s[*i])
        return -1; // quote non fermée
    (*i)++; // skip fermeture
    return 0;
}

// Calcule la longueur d'un argument (sans copier)
int get_arg_length(const char *s, int *i)
{
    int start = *i;

    // skip espaces
    while (s[*i] && ft_isspace(s[*i]))
        (*i)++;
    if (!s[*i])
        return 0;

    // token spécial
    if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
    {
        (*i)++;
        return 1;
    }

    // lecture normale
    while (s[*i] && !ft_isspace(s[*i]) && s[*i] != '|' && s[*i] != '<' && s[*i] != '>')
    {
        if (s[*i] == '\'' || s[*i] == '"')
        {
            if (skip_quoted(s, i, s[*i]) == -1)
                return -1;
        }
        else
            (*i)++;
    }

    return *i - start;
}

// Extrait un argument en supprimant les quotes
char *get_one_arg(const char *s, int *i)
{
    int start = *i;
    int len = get_arg_length(s, i);
    if (len <= 0)
        return NULL;

    char *arg = malloc(len + 1);
    if (!arg)
        return NULL;

    int j = 0;
    int k = start;

    while (k < *i)
    {
        if (s[k] == '\'' || s[k] == '"')
        {
            char qc = s[k++];
            while (k < *i && s[k] != qc)
                arg[j++] = s[k++];
            if (s[k] == qc)
                k++; // skip fermeture
        }
        else
        {
            if (ft_isspace(s[k]))
                k++;
            else
                arg[j++] = s[k++];
        }
    }
    arg[j] = '\0';
    return arg;
}


char *replace_envvar(char *s, t_data *d)
{
    int i = 0;
    int j = 0;
    char *envvar = ft_itoa(d->exit_status);
    if (envvar == NULL)
    {
        perror("failed to allocate envvar");
        free(envvar);
        return (NULL);
    }
    char *arg = malloc(sizeof(char) * ft_strlen(s) + ft_strlen(envvar) + 1);
    if (!arg)
    {
        perror("failed to allocate");
        free(envvar);
        return (NULL);
    }

    while (s[i])
    {
        if (s[i] == '$' && s[i + 1] == '?')
        {
            int k = 0;
            while (envvar[k])
                arg[j++] = envvar[k++];
            i += 2;
        }
        else
            arg[j++] = s[i++];
    }
    arg[j] = '\0';
    free(envvar);
    return (arg);
}
