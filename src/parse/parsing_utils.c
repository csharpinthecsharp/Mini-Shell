/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:34:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 20:38:01 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int get_arg_length(char *s, int *i, int *quoted, char *quote_char)
{
    int start_i;

    // Sauter les espaces
    while (s[*i] && ft_isspace(s[*i]))
        (*i)++;
    if (!s[*i])
        return 0;
    *quoted = 0;
    *quote_char = 0;
    // Vérifier si l’argument commence par un guillemet
    if (s[*i] == QUOTE || s[*i] == BIG_QUOTE)
    {
        *quoted = 1;
        *quote_char = s[*i];
        (*i)++;
    }
    start_i = *i;
    if (!*quoted && (s[*i] == '|' || s[*i] == '<' || s[*i] == '>'))
    {
        (*i)++;
        return 1; // le caractère est un token à part
    }

    // Lire jusqu’à la fin du guillemet ou jusqu’à un espace
    if (*quoted)
    {
        while (s[*i] && s[*i] != *quote_char)
            (*i)++;
    }
    else
    {
        while (s[*i] && !ft_isspace(s[*i]))
            (*i)++;
    }
    return *i - start_i;
}

/*
** Extrait un seul argument et le retourne sous forme de chaîne.
** Utilise get_arg_length pour déterminer la taille.
*/
char *get_one_arg(char *s, int *i)
{
    int quoted;
    char quote_char;
    int word_len = get_arg_length(s, i, &quoted, &quote_char);
    if (word_len == 0)
        return NULL;
    char *arg = malloc(word_len + 1);
    if (!arg)
        return NULL;
    // Copier l’argument
    int j = 0;
    int start_i = *i - word_len;
    while (j < word_len)
    {
        arg[j] = s[start_i + j];
        j++;
    }
    arg[word_len] = '\0';
    // Sauter le guillemet fermant si présent
    if (quoted && s[*i] == quote_char)
        (*i)++;
    return (arg);
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
