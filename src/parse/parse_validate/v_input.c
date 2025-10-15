/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:46:28 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 15:40:15 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int check_redirection_syntax(char *input)
{
    int i = 0;
    char quote = 0;

    while (input[i])
    {
        if ((input[i] == '\'' || input[i] == '"') && quote == 0)
            quote = input[i];
        else if (input[i] == quote)
            quote = 0;

        if (quote)
        {
            i++;
            continue;
        }

        if (input[i] == '>' || input[i] == '<')
        {
            int type = input[i];
            i++;

            if (input[i] == type)
                i++;

            while (input[i] && input[i] == ' ')
                i++;

            if (!input[i])
            {
                print_error("syntax error near unexpected token `newline'", "!");
                return (FAILED);
            }

            if (input[i] == '>' || input[i] == '<' || input[i] == '|')
            {
                char token[3] = {input[i], 0, 0};
                if (input[i + 1] == input[i])
                    token[1] = input[i];
                print_error("syntax error near unexpected token", token);
                return FAILED;
            }
        }
        else
            i++;
    }

    if (quote)
    {
        print_error("syntax error: unmatched quote", "!");
        return FAILED;
    }

    return SUCCESS;
}

int check_in_check_pipe(char *input, int *pos)
{
    if (input[(*pos)] == '|' && input[(*pos) + 1] == '|')
    {
        print_error("syntax error near unexpected token `||'", "!");
        return (FAILED);
    }

    if (input[*pos] == '|' && input[(*pos) + 1])
    {
        int j = (*pos) + 1;
        while (input[j] == ' ')
            j++;
        if (input[j] == '|')
        {
            print_error("syntax error near unexpected token `|'", "!");
            return (FAILED);
        }
    }
    return (SUCCESS);
}

int check_pipe_syntax(char *input)
{
    int i = 0;
    char quote = 0;
    while (ft_isspace(input[i]))
        i++;
    if (input[i] == '|')
    {
        print_error("syntax error near unexpected token `|'", "!");
        return (FAILED);
    }
    while (input[i])
    {
        if ((input[i] == '\'' || input[i] == '"') && quote == 0)
            quote = input[i];
        else if (input[i] == quote)
            quote = 0;
        if (quote)
        {
            i++;
            continue;
        }
        if (check_in_check_pipe(input, &i) == 1)
            return (FAILED);
        i++;
    }
    return (SUCCESS);
}

 