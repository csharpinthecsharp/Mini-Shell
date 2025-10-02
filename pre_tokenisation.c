/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_tokenisation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:34:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/02 15:57:13 by ltrillar         ###   ########.fr       */
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
int zzz(t_data *d)
{
    d->c_quote = count_quotes(d->input);
    // SI LE NOMBRE EST IMPAIR
    if (d->c_quote % 2 != 0)
        return (1);
    
    // SI IL N'Y A PAS DE QUOTES
    if (d->c_quote > 1)
    {
        // STATE 1 = QUOTES 
        d->c_pipe = count_arg(d->input, QUOTE_TRUE, PIPE);
        d->c_big_quote = count_arg(d->input, QUOTE_TRUE, BIG_QUOTE);
        if (d->c_big_quote % 2 != 0)
            return (1);
        d->c_env_var = count_arg(d->input, QUOTE_TRUE, ENV_VAR);
    }
    else
    {
        // STATE 0 = NO QUOTES
        d->c_pipe = count_arg(d->input, QUOTE_FALSE, PIPE);
        d->c_big_quote = count_arg(d->input, QUOTE_FALSE, BIG_QUOTE);
        if (d->c_big_quote % 2 != 0)
            return (1);
        d->c_env_var = count_arg(d->input, QUOTE_FALSE, ENV_VAR);
    }
    return (0);
}
