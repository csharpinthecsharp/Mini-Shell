/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:34:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/02 13:36:59 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define QUOTE_TRUE 1
#define QUOTE_FALSE 0
#define PIPE '|'
#define QUOTE '\''
#define BIG_QUOTE '\"'
#define ENV_VAR '$'

static int is_in_arg(char *input, int pos, char arg)
{
    int left = 0;
    int right = 0;
    int i = 0;
    // On compte les quote avant la pos
    while (i < pos && input[i] != '\0')
    {
        if (input[i] == arg)
            left++;
        i++;
    }

    // On compte les quote après la pos
    i = pos + 1;
    while (input[i] != '\0')
    {
        if (input[i] == arg)
            right++;
        i++;
    }
    
    if (left % 2 == 1 && right > 0)
        return QUOTE_TRUE;

    return QUOTE_FALSE;
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

static int count_arg(char *input, int state, char arg)
{
    int i = 0;
    int count = 0;
    if (state == QUOTE_TRUE)
    {
        while (input[i]) 
        {
            if (arg == ENV_VAR)
            {
                if ((input [i] == arg) && !is_in_arg(input, i, QUOTE))
                    count++;
            }
            else if ((input[i] == arg) && !is_in_arg(input, i, BIG_QUOTE)
                && !is_in_arg(input, i, QUOTE))
                count++;
            i++;
        }
    }
    else
    {
        while (input[i])
        {
            if (input[i] == arg)
                count++;
            i++;
        }
    }
    return (count);
}

// RETURN 1 = OPEN QUOTE
// RETURN 2 = NO QUOTES
int zzz(char *input)
{
    int pipe_count = 0;
    int quote_count = 0;
    int env_var_count = 0;
    int big_quote_count = 0;
    
    quote_count = count_quotes(input);
    // SI LE NOMBRE EST IMPAIR
    if (quote_count % 2 != 0)
        return (1);
    // SI IL N'Y A PAS DE QUOTES

    if (quote_count > 1)
    {
        // STATE 1 = QUOTES 
        pipe_count = count_arg(input, QUOTE_TRUE, PIPE);
        big_quote_count = count_arg(input, QUOTE_TRUE, BIG_QUOTE);
        env_var_count = count_arg(input, QUOTE_TRUE, ENV_VAR);
    }
    else
    {
        // STATE 0 = NO QUOTES
        pipe_count = count_arg(input, QUOTE_FALSE, PIPE);
        big_quote_count = count_arg(input, QUOTE_TRUE, BIG_QUOTE);
        env_var_count = count_arg(input, QUOTE_FALSE, ENV_VAR);
    }
    
    printf("Pipe Count: %d | Quote Count: %d | Env Var: %d | B quote: %d\n", pipe_count, quote_count, env_var_count, big_quote_count);

    return (0);
}
