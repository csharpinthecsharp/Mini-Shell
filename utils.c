/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:20:39 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/29 00:22:56 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_countword(char *input)
{
    int i = 0;
    int words = 0;
    int in_word = 0;

    if (input == NULL)
        return (0);

    while (input[i])
    {
        if (input[i] == ' ')
            in_word = 0;
        else if (!in_word)
        {
            in_word = 1;
            words++;
        }
        i++;
    }
    return (words);
}

void print_error(char *str_sub, char *str_cont)
{
    printf(ERROR_PREFIX "%s%s\n" RESET, str_sub, str_cont);
}