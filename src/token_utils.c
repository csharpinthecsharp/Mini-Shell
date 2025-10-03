/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:34:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/04 01:44:10 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int count_quotes(char *input)
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

int count_big_quotes(char *input)
{
    int i = 0;
    int count = 0;
    while (input[i])
    {
        if (input[i] == BIG_QUOTE)
            count++;
        i++;
    }
    return (count);
}

