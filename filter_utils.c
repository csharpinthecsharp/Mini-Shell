/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/29 20:15:55 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_quotes(char *str)
{
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == '\'')
            count++;
    return count / 2;
}

void retrieve_quoted(t_data *d, char *str)
{
    int i = 0;
    int idx = 0;

    while (str[i])
    {
        if (str[i] == '\'')
        {
            int y = i + 1;
            while (str[y] && str[y] != '\'')
                y++;

            if (str[y] == '\'')
            {
                int len = y - i - 1;
                char *tmp = malloc(len + 1);
                if (!tmp)
                    return;

                int j = 0;
                for (int k = i + 1; k < y; k++)
                    tmp[j++] = str[k];
                tmp[j] = '\0';

                d->input_quote[idx++] = tmp;
                i = y;
            }
        }
        i++;
    }
    d->input_quote[idx] = NULL;
}
