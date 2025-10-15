/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:46:28 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 02:51:18 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int check_redirection_syntax(char *input)
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
                return FAILED;
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

static int check_pipe_syntax(char *input)
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

        if (input[i] == '|' && input[i + 1] == '|')
        {
            print_error("syntax error near unexpected token `||'", "!");
            return FAILED;
        }

        if (input[i] == '|' && input[i + 1])
        {
            int j = i + 1;
            while (input[j] == ' ')
                j++;
            if (input[j] == '|')
            {
                print_error("syntax error near unexpected token `|'", "!");
                return FAILED;
            }
        }
        i++;
    }
    return (SUCCESS);
}

int global_check(t_data *d)
{
    if (check_pipe_syntax(d->input) == FAILED)
    {
        d->exit_status = 2;
        return (FAILED);
    }
    if (check_redirection_syntax(d->input) == FAILED)
    {
        d->exit_status = 2;
        return (FAILED);
    }
    return (SUCCESS);
}
 