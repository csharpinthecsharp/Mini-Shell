/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_args.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:34:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/16 01:53:03 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int skip_quoted(const char *s, int *i, char quote_char)
{
    (*i)++;
    while (s[*i] && s[*i] != quote_char)
        (*i)++;
    (*i)++;
    return 0;
}

int get_arg_length(const char *s, int *i, int *is_dquote)
{
    int start;
    
    start = *i;
    while (s[*i] && ft_isspace(s[*i]))
        (*i)++;
    if (!s[*i])
        return 0;
    if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
    {
        if (s[*i + 1] == '<' && s[*i] == '<')
            (*i)+=2;
        else if (s[*i + 1] == '>' && s[*i] == '>')
            (*i)+=2;
        else 
            (*i)+=1;
        return 1;
    }
    while (s[*i] && !ft_isspace(s[*i]) && s[*i] != '|' && s[*i] != '<' && s[*i] != '>')
    {
        if (s[*i] == '\'' || s[*i] == '"')
        {
            if (s[*i] == '\'')
                (*is_dquote) = 1;
            skip_quoted(s, i, s[*i]);
        }
        else
            (*i)++;
    }
    return *i - start;
}

int loop_into_arg(int i, char *s, int k, char *arg, int *j)
{
    if (s[k] == '\'' || s[k] == '"')
    {
        char qc = s[k++];
        while (k < i && s[k] != qc)
            arg[(*j)++] = s[k++];
        if (s[k] == qc)
            k++;
    }
    else
    {
        if (ft_isspace(s[k]))
            k++;
        else
            arg[(*j)++] = s[k++];
    }
    return k;
}


char *get_one_arg(char *s, int *i, int *is_dquote)
{
    int start;
    int j;
    int k;
    
    start = *i;
    int len;
    
    len = get_arg_length(s, i, is_dquote);
    if (len <= 0)
        return (NULL);
    char *arg = malloc(len + 1);
    if (!arg)
        return (NULL);

    j = 0;
    k = start;
    while (k < *i)
        k = loop_into_arg(*i, s, k, arg, &j);
    arg[j] = '\0';
    return arg;
}

