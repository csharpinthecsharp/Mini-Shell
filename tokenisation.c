/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/02 15:49:16 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **split(t_data *d)
{
    if (d->c_quote == 0 && d->c_big_quote == 0
        && d->c_env_var == 0 && d->c_pipe == 0)
        return (ft_split(d->input, ' '));
    return (NULL);
}

int filter_input(t_data *d, char *envp[])
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    if (d->input == NULL)
        return (0);

    if (zzz(d) == 1)
        print_error("Error: ", "Open quote");

    d->input_splitted = split(d);
    int i = 0;
    while (d->input_splitted[i])
    {
        printf("%s\n", d->input_splitted[i]);
        i++;
    }
    return (0);

        
    
    if (check_command(d->input_splitted) == 0)
        print_error("command not found: ", d->input_splitted[0]);
    else if (check_command(d->input_splitted) == 1)
    {
        if (run_custom_cmd(d) == 1)
            return (1);
    }
    else if (check_command(d->input_splitted) == 2)
    {
        if (run_build_cmd(d, envp) == 1)
            return (1);
    }
    return (0);
}