/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:16:18 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/19 20:46:16 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void heredoc(t_data *d, int *pos, int i)
{
    char *res = NULL;
    char *delimiter = d->output_file[*pos][i];
    int heredoc[2];
    int stdin;
    
    if (pipe(heredoc) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    stdin = dup(STDIN_FILENO);
    if (stdin == -1)
    {
        perror("dup");
        close(heredoc[0]);
        close(heredoc[1]);
        return ;
    }
    int pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(heredoc[0]);
        close(heredoc[1]);
        close(stdin);
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0)
    {
        close(heredoc[0]);
        close(stdin);
        signal(SIGINT, heredoc_ctrl_c);
        
        while (1)
        {
            res = readline("> ");
            if (!res)
            {
                print_error("here-document delimited by end-of-file", "warning");
                d->exit_status = 0;
                break;
            }
            if (strcmp(res, delimiter) == 0)
            {
                free(res);
                break;
            }
            ft_putstr_fd(res, heredoc[1]);
            ft_putstr_fd("\n", heredoc[1]);
            free(res);
        }
        close(heredoc[1]);
        exit(0);
    }
    else
    {
        close(heredoc[1]);
        
        int status;
        signal(SIGINT, SIG_IGN);
        waitpid(pid, &status, 0);
        
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        {
            close(heredoc[0]);
            close(stdin);

            rl_on_new_line();
            rl_replace_line("", 0);
            
            signal(SIGINT, handler_ctrl_c);
            return;
        }
        signal(SIGINT, handler_ctrl_c);
        dup2(heredoc[0], STDIN_FILENO);
        close(heredoc[0]);

        d->stdin_back = stdin;
    }
}