/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:21:48 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/29 23:18:14 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *ft_word_alloc(const char *s, size_t start, size_t end)
{
    char *word;
    size_t i = 0;

    word = malloc(end - start + 1);
    if (!word)
        return (NULL);
    while (start < end)
        word[i++] = s[start++];
    word[i] = '\0';
    return (word);
}

static int count_tokens(const char *s)
{
    int i = 0, count = 0;
    while (s[i])
    {
        while (s[i] && (s[i] == ' ' || s[i] == '\t'))
            i++;
        if (!s[i])
            break;
        count++;
        if (s[i] == '\'' || s[i] == '"')
        {
            char quote = s[i++];
            while (s[i] && s[i] != quote)
                i++;
            if (s[i])
                i++;
        }
        else
        {
            while (s[i] && s[i] != ' ' && s[i] != '\t'
                   && s[i] != '\'' && s[i] != '"')
                i++;
        }
    }
    return count;
}

char **ft_split_quotes(const char *s)
{
    int i = 0, idx = 0;
    int count = count_tokens(s);
    char **tab = malloc(sizeof(char *) * (count + 1));
    if (!tab)
        return (NULL);

    while (s[i])
    {
        while (s[i] && (s[i] == ' ' || s[i] == '\t'))
            i++;
        if (!s[i])
            break;
        if (s[i] == '\'' || s[i] == '"')
        {
            char quote = s[i++];
            int start = i;
            while (s[i] && s[i] != quote)
                i++;
            tab[idx++] = ft_word_alloc(s, start, i);
            if (s[i])
                i++; 
        }
        else
        {
            int start = i;
            while (s[i] && s[i] != ' ' && s[i] != '\t'
                   && s[i] != '\'' && s[i] != '"')
                i++;
            tab[idx++] = ft_word_alloc(s, start, i);
        }
    }
    tab[idx] = NULL;
    return tab;
}
