/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:16:46 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 15:52:05 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void alloc_parse_args(char ***argv, int len)
{
    *argv = malloc(sizeof(char *) * (len + 1));
    if (!argv)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
}   