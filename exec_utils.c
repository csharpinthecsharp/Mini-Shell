/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:57:15 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/02 13:14:23 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_command(char **argv)
{
    // return 0 = on a pas trouvé de commande dedans.
    // return 1 = on a trouvé une commande qu'il faut build.
    // return 2 = pas besoin de la build, juste execve.
    int len = ft_strlen(argv[0]);
    if (ft_strncmp(argv[0], "ls", len) == 0)
        return (2);
    else if (ft_strncmp(argv[0], "cat", len) == 0)
        return (2);
    else if (ft_strncmp(argv[0], "pwd", len) == 0)
        return (1);
    else if (ft_strncmp(argv[0], "exit", len) == 0)
        return (1);
    else if (ft_strncmp(argv[0], "echo", len) == 0)
        return (1);
    return (0);
}

int filter_input(t_data *d, char *envp[])
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    if (d->input == NULL)
        return (0);


    if (filter_quote(d) == 1)
        return 0;
    else 
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

int run_custom_cmd(t_data *d)
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    int count = 0;

    while (d->input_splitted[count])
        count++;
    if (ft_strncmp(d->input_splitted[0], "pwd", 3) == 0)
    {
        if (handle_pwd(d->input_splitted[0], count, d->path) == 1)
            return (1);
    }
    else if (ft_strncmp(d->input_splitted[0], "exit", 4) == 0)
    {
        if (handle_exit(d->input_splitted[0], count) == 1)
            return (1);
    }
    else if (ft_strncmp(d->input_splitted[0], "echo", 4) == 0)
    {
        if (handle_echo(d->input_splitted, count) == 1)
            return (1);
    }
    return (0);
}

int run_build_cmd(t_data *d, char *envp[])
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    pid_t pid;
    pid = fork();
    if (pid == 0)
    {
        int count = 0;
        while (d->input_splitted[count])
            count++;
        char **argv = malloc(sizeof(char *) * count + 2);
        if (!argv)
            return (1);
        argv[0] = ft_strjoin("/bin/", d->input_splitted[0]);

        int i = 1;
        while (i < count)
        {
            argv[i] = d->input_splitted[i];
            i++;
        }
        argv[i] = NULL;
            
        execve(argv[0], argv, envp);
        perror("execve failed");
        free(argv);
        exit(EXIT_FAILURE);
    }
    else
        wait(NULL);
    return (0);
}