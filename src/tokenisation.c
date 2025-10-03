/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/03 04:13:16 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int locate(char *s, char arg, int *arg_storage)
{
	int i = 0;
    int i_arg = 0;
	int len = ft_strlen(s);

    arg_storage = malloc(sizeof(int) * len + 1);
    if (!arg_storage)
        return (1);
        
    while (s[i])
    {
        if (s[i] == arg)
        {
            arg_storage[i_arg] = i;
            printf("%c : , %d\n",arg, i);
            i_arg++;
        }
        i++;
    }
    s[i] = '\0';
    return (0);
}

static int ft_isspace(char arg)
{
    if (arg == ' ' || arg == '\t')
        return (1);
    return (0);
}

static char *get_content(char *s, int start, int end)
{
    
}

static char *get_command(char *s)
{
    int i = 0;
    int len = ft_strlen(s);

    //char **argv = malloc(sizeof(char *) * len + 1);
    //if (!argv)
        //return NULL;

    //argv[0] = malloc(sizeof(char) * (len + 1));
    char *argv = malloc(sizeof(char) * (len + 1));
    if (!argv)
        return NULL;

    while (ft_isspace(s[i]))
        i++;

    int j = 0;
    while (s[i] && !ft_isspace(s[i]))
        //argv[0][j++] = s[i++];
        argv[j++] = s[i++];
    argv[j] = '\0';
    //argv[1] = NULL;

    return argv;
}

static char **split_utils(char *s, t_data *d)
{
    char *cmd = get_command(s);
    char *content;
}

static char **split(t_data *d)
{
    if (locate_init(d) == 1)
        return (NULL);
    
    if (d->c_quote == 0 && d->c_big_quote == 0
        && d->c_env_var == 0 && d->c_pipe == 0)
        return (ft_split(d->input, ' '));
    else
        return (split_utils(d->input, d));
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
    if (d->input_splitted == NULL)
        return (1);
    
    int i = 0;
    while (d->input_splitted[i])
    {
        printf("%s", d->input_splitted[i]);
        printf(" ");
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
