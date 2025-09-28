/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:57:15 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/28 21:09:46 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_command(t_data *d)
{
    if (d->input == NULL)
        return (0);
        
    if (ft_strncmp(d->input, "ls", 2) == 0)
        return (1);
        
    else if (ft_strncmp(d->input, "cat", CAT_SIZE) == 0)
    {
        d->input_splitted = ft_split(d->input, ' ');
        return (2);
    }
    return (0);
}

int try_input(t_data *d, char *envp[])
{
    // Parent
    // └── fork()
    //      ├── Enfant → execve("ls") → remplace par /bin/ls
    //      │             ↳ si erreur → perror + exit
    //      └── Parent → wait(NULL) → attend la fin de l’enfant
    pid_t pid;
    if (check_command(d) == 1)
    {
        pid = fork();
        if (pid == 0)
        {
            char *path = ft_strjoin("/bin/", d->input);
            char *ls_path[] = {path, NULL};
            execve(ls_path[0], ls_path, envp);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        else
            wait(NULL);
    }
    else if (check_command(d) == 2)
    {
        pid = fork();
        if (pid == 0)
        {
            int count = 0;
            while (d->input_splitted[count])
                count++;
            char **argv = malloc(sizeof(char *) * count + 2);
            if (!argv)
                exit(EXIT_FAILURE);
            argv[0] = "/bin/cat";

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
    }
    return (0);
}