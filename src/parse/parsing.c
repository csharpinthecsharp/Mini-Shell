/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 15:17:10 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Pour chaques lignes de commandes envoyée à votre programme, plein de choses seront faite mais la plus important des choses à faire est de se créer une liste chainée de token pour chaques éléments de la ligne de commande.
La liste chainée aura une str et un int pour chaque maillon, la str sera le "mot" et l'int le token. Prenons l'exemple de la pire ligne de commande possible : cat|ls (on remarquera qu'il n'y a pas d'espace et c'est normal)

    le premier token aura comme str "cat" avec CMD comme type (6).
    le deuxieme token aura comme str "|" avec PIPE comme type (5).
    le dernier token aura comme str "ls" avec CMD comme type (6).

(se referer à minishell.h)

Les règles sont simple :

    Si on croise une redirection (<, >, << ou >>) alors le token sera soit INPUT (1), soit TRUNC (3), soit HEREDOC (2) ou soit APPEND (4) respectivement.
    Le premier token sera CMD (6) si pas de redirection.
    Les tokens après un CMD ou une redirection seront ARG (7).
    Si "|" est la str avec il aura le type PIPE (5).
    Après un pipe le prochain token sera soit une redirection soit CMD.

Les tokens ne sont pas la première étape du parsing mais ils sont la clé d'un minishell simple à faire.*/
#include "../../include/minishell.h"

/*
** Découpe la chaî<ne en arguments.
** Retourne un tableau de chaînes terminé par NULL.
*/
char **get_args(char *s, t_data *d)
{
    int i = 0;
    int k = 0;
    int is_dquote = 0;
    int len = ft_strlen(s);
    char **argv = malloc(sizeof(char *) * (len + 1));
    if (!argv)
        return NULL;

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
    char ***cmds = malloc(sizeof(char **) * (10000));
    if (!cmds)
        return NULL;

    int i = 0, cmds_i = 0, arg_i = 0;
    cmds[cmds_i] = malloc(sizeof(char *) * (10001));
    if (!cmds[cmds_i])
        return NULL;

    while (argv[i])
    {
        
        if (argv[i][0] == PIPE && argv[i][1] == '\0') // pipe isolé
        {
            cmds[cmds_i][arg_i] = NULL; // terminer la commande
            cmds_i++;
            arg_i = 0;
            cmds[cmds_i] = malloc(sizeof(char *) * (10000 + 1));
            if (!cmds[cmds_i])
                return NULL;
        }
        else
        {
            cmds[cmds_i][arg_i] = ft_strdup(argv[i]);
            arg_i++;
        }
        i++;
    }
    cmds[cmds_i][arg_i] = NULL; // terminer la dernière commande
    cmds[cmds_i + 1] = NULL;    // terminer le tableau de commandes
    return cmds;
}

char **split(t_data *d)
{
    char **argv = get_args(d->input, d);
    if (!argv)
        return (NULL);
    return (argv);
}

