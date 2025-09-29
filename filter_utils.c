/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/29 23:17:11 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int filter_quote(t_data *d)
{
    int quotes;

    // Si il y a des quotes on va les fix
    quotes = count_quotes(d->input);

    d->input_splitted = malloc(sizeof(char *) * BUFFER_SIZE + 1);
    if (!d->input_splitted)
        return (1);
    
    if (quotes < 0)
        d->input_splitted = ft_split(d->input, ' ');
    else
        d->input_splitted = ft_split_quotes(d->input);
    return (0);
}

int count_quotes(char *str)
{
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == '\'')
            count++;
    for (int i = 0; str[i]; i++)
        if (str[i] == '"')
            count++;
    return count / 2;
}

