/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/03 18:10:44 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int ft_isspace(char arg)
{
    if (arg == ' ' || arg == '\t')
        return (1);
    return (0);
}


static char *get_first_arg(char *s)
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

static char **get_args(char *s, int start)
{
    char **argv = malloc(sizeof(char *) * ft_strlen(s));
    if (!argv)
        return (NULL);
    int i = start;
    int k = 0;
    while (ft_isspace(s[i]))
        i++;
    while (s[i])
    {
        int world_len = 0;
        while (s[i + world_len] && !ft_isspace(s[i + world_len]))
            world_len++;
        argv[k] = malloc(sizeof(char) * (world_len + 1));
        if (!argv[k])
            return (NULL);
            
        int j = 0;
        while (j < world_len)
        {
            argv[k][j] = s[i++];
            j++;
        }
        argv[k][world_len] = '\0';
        k++;
        while (ft_isspace(s[i]))
            i++;
    }
    argv[k] = NULL;
    return (argv);
}

static char **split(t_data *d)
{
    char *f_arg = get_first_arg(d->input);
    if (!f_arg)
        return (NULL);
        
    int len_f_arg = ft_strlen(f_arg);
    char **argv = get_args(d->input, len_f_arg);  
    if (!argv)
        return (NULL);
        
    printf("first arg: %s\n", f_arg);
    free(f_arg);
    return (argv);
}

// JE VEUX ***COMMANDS, qui contient des **INPUT_SPLITTED et *INPUT
// SO WHILE (COMMANDS[i])
    // run(commands[i]) link to commands[i] if | < > tu captes le delire
int filter_input(t_data *d, char *envp[])
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    if (d->input == NULL)
        return (0);

    if (count_quotes(d->input) % 2 != 0)
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
