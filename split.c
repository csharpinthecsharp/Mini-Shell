/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:34:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/02 01:25:23 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define QUOTE_TRUE 1
#define QUOTE_FALSE 0
#define PIPE '|'
#define QUOTE '\''

static int is_in_quotes(char *input, int pos)
{
    int i = pos;
    int count = 0;
    if (input[i] || input[i] + 1)
        return (QUOTE_FALSE);
    while (input[i])
    {
        if (input[i] == QUOTE)
        {
            count++;
            break;
        }
        i++;
    }
    input = '\0';
    i = pos - 1;
    while (i != 0)
    {
        if (input[i] == QUOTE)
        {
            count++;
            break;
        }
    }
    if (count == 2) 
        return (QUOTE_TRUE);
    return (QUOTE_FALSE);
}

static int count_quotes(char *input)
{
    int i = 0;
    int count = 0;
    while (input[i])
    {
        if (input[i] == QUOTE)
            count++;
        i++;
    }
    return (count);
}

static int count_pipe(char *input, int state)
{
    int i = 0;
    int count = 0;
    if (state == QUOTE_TRUE)
    {
        while (input[i]) 
        {
            if (input[i] == PIPE && !is_in_quotes)
                count++;
        }
    }
    else
    {
        while (input[i])
        {
            if (input[i] == PIPE)
                count++;
        }
    }
    return (count);
}

// RETURN 1 = OPEN QUOTE
// RETURN 2 = NO QUOTES
void zzz(char *input)
{
    int pipe_count = 0;
    int quote_count = 0;

    quote_count = count_quotes(input);
    // SI LE NOMBRE EST IMPAIR
    if (quote_count % 2 != 0)
        return (1);
    // SI IL N'Y A PAS DE QUOTES

    if (quote_count > 1)
        // STATE 1 = QUOTES 
        pipe_count = count_pipe(input, QUOTE_TRUE);
    else
        // STATE 0 = NO QUOTES
        pipe_count = count_pipe(input, QUOTE_FALSE);
    
    
}