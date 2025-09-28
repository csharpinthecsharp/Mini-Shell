/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:57:15 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/28 15:30:35 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_command(char *input)
{
    if (input == NULL)
        return (0);
    if (ft_strncmp(input, "ls", 2) == 0)
        return (1);
    if (ft_strncmp(input, "cat", 3) == 0)
        return (1);
    return (0);
}
int try_input(char *input, char *envp[])
{
    // Parent
    // └── fork()
    //      ├── Enfant → execve("ls") → remplace par /bin/ls
    //      │             ↳ si erreur → perror + exit
    //      └── Parent → wait(NULL) → attend la fin de l’enfant
    pid_t pid;
    if (check_command(input) == 1)
    {
        pid = fork();
        if (pid == 0)
        {
            char *path = ft_strjoin("/bin/", input);
            char *ls_path[] = {path, NULL};
            execve(ls_path[0], ls_path, envp);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        else
            wait(NULL);
    }
    return (0);
}