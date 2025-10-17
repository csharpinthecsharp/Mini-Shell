/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/17 15:34:08 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char **get_args(char *s, t_data *d)
{
    int i = 0;
    int k = 0;
    int is_dquote = 0;
    int len = ft_strlen(s);
    char **argv;
    argv = NULL;
    alloc_parse_args(&argv, len);
    while (s[i])
    {
        char *raw_arg = get_one_arg(s, &i, &is_dquote);
        if (!raw_arg)
            break;
        char *arg = replace_envvar(raw_arg, d, &is_dquote);
        free(raw_arg);
        if (!arg)
            break;
        argv[k++] = arg;
    }
    argv[k] = NULL;
    return argv;
}

char ***split_commands(char **argv)
{
    int i = 0, cmds_i = 0, arg_i = 0;

    // tableau de commandes (NULL-terminé)
    char ***cmds = malloc(sizeof(char **) * 2);
    if (!cmds) return NULL;

    // tableau d'arguments pour la première commande
    int arg_cap = 4; // capacité initiale
    cmds[cmds_i] = malloc(sizeof(char *) * arg_cap);
    if (!cmds[cmds_i]) return NULL;

    while (argv[i])
    {
        if (strcmp(argv[i], "|") == 0)
        {
            // fin de la commande courante
            cmds[cmds_i][arg_i] = NULL;
            cmds_i++;
            arg_i = 0;

            // agrandir le tableau de commandes
            char ***tmp = realloc(cmds, sizeof(char **) * (cmds_i + 2));
            if (!tmp) return NULL;
            cmds = tmp;

            // nouvelle commande
            arg_cap = 4;
            cmds[cmds_i] = malloc(sizeof(char *) * arg_cap);
            if (!cmds[cmds_i]) return NULL;
        }
        else
        {
            // agrandir si nécessaire
            if (arg_i >= arg_cap - 1)
            {
                arg_cap *= 2;
                char **tmp = realloc(cmds[cmds_i], sizeof(char *) * arg_cap);
                if (!tmp) return NULL;
                cmds[cmds_i] = tmp;
            }
            cmds[cmds_i][arg_i] = strdup(argv[i]);
            arg_i++;
        }
        i++;
    }

    // terminer la dernière commande
    cmds[cmds_i][arg_i] = NULL;
    cmds[cmds_i + 1] = NULL;

    return cmds;
}

char **split(t_data *d)
{
    char **argv = get_args(d->input, d);
    if (!argv)
        return (NULL);
    return (argv);
}

