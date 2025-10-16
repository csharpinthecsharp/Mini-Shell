/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_helper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:32:50 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/16 02:00:41 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int count_args(char **argv, int start)
{
    int count = 0;
    while (argv[start] && !(argv[start][0] == '|' && argv[start][1] == '\0'))
    {
        count++;
        start++;
    }
    return (count);
}

static char *get_env_string(t_data *d, char *s)
{
    char *arg = malloc(sizeof(char) * 1000);
    int i = 0;
    int j = 0;
    
    if (s[i] == '$')
        i++;
    while (s[i] && !ft_isspace(s[i]) && s[i] != '$')
        arg[j++] = s[i++];
    arg[j] = '\0';
    
    j = 0;
    while (d->envp[j])
    {
        if (ft_strncmp(d->envp[j], arg, ft_strlen(arg)) == 0
        && d->envp[j][ft_strlen(arg)] == '=')
        {
            return (ft_strdup(getenv(arg)));
        }
        j++;
    }
    free(arg);
    return (ft_strdup(""));
}

char *replace_envvar(char *s, t_data *d, int *is_dquote)
{
    int i = 0;
    int j = 0;
    char *envvar = ft_itoa(d->exit_status);
    if (envvar == NULL)
    {
        perror("failed to allocate envvar");
        free(envvar);
        return (NULL);
    }
    char *arg = malloc(sizeof(char) * ft_strlen(s) + ft_strlen(envvar) + 256);
    if (!arg)
    {
        perror("failed to allocate");
        free(envvar);
        return (NULL);
    }

    while (s[i])
    {
        if (s[i] == '$' && s[i + 1] == '?' && *is_dquote == 0)
        {
            int k = 0;
            while (envvar[k])
                arg[j++] = envvar[k++];
            i += 2;
        }
        else if (s[i] == '$' && *is_dquote == 0)
        {
            char *env_value = get_env_string(d, s + i);
            int k = 0;
            while (env_value[k])
            {
                arg[j++] = env_value[k];
                k++;
            }
            if (env_value[0] != '\0')
                i++; // skip $
            while (s[i] && !ft_isspace(s[i]) && s[i] != '$')
                i++; 
            free(env_value);
        }
        arg[j++] = s[i++];
    }
    arg[j] = '\0';
    free(envvar);
    return (arg);
}