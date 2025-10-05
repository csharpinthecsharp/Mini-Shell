/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 15:52:23 by ltrillar         ###   ########.fr       */
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

static int ft_isspace(char arg)
{
    if (arg == ' ' || arg == '\t')
        return (1);
    return (0);
}
static char *replace_envvar(char *s, t_data *d)
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
    char *arg = malloc(sizeof(char) * ft_strlen(s) + ft_strlen(envvar) + 1);
    if (!arg)
    {
        perror("failed to allocate");
        free(envvar);
        return (NULL);
    }

    while (s[i])
    {
        if (s[i] == '$' && s[i + 1] == '?')
        {
            int k = 0;
            while (envvar[k])
                arg[j++] = envvar[k++];
            i += 2;
        }
        else
            arg[j++] = s[i++];
    }
    arg[j] = '\0';
    free(envvar);
    return (arg);
}

static int get_arg_length(char *s, int *i, int *quoted, char *quote_char)
{
    int start_i;

    // Sauter les espaces
    while (s[*i] && ft_isspace(s[*i]))
        (*i)++;
    if (!s[*i])
        return 0;
    *quoted = 0;
    *quote_char = 0;
    // Vérifier si l’argument commence par un guillemet
    if (s[*i] == QUOTE || s[*i] == BIG_QUOTE)
    {
        *quoted = 1;
        *quote_char = s[*i];
        (*i)++;
    }
    start_i = *i;
    if (!*quoted && (s[*i] == '|' || s[*i] == '<' || s[*i] == '>'))
    {
        (*i)++;
        return 1; // le caractère est un token à part
    }

    // Lire jusqu’à la fin du guillemet ou jusqu’à un espace
    if (*quoted)
    {
        while (s[*i] && s[*i] != *quote_char)
            (*i)++;
    }
    else
    {
        while (s[*i] && !ft_isspace(s[*i]))
            (*i)++;
    }
    return *i - start_i;
}

/*
** Extrait un seul argument et le retourne sous forme de chaîne.
** Utilise get_arg_length pour déterminer la taille.
*/
static char *get_one_arg(char *s, int *i)
{
    int quoted;
    char quote_char;
    int word_len = get_arg_length(s, i, &quoted, &quote_char);
    if (word_len == 0)
        return NULL;
    char *arg = malloc(word_len + 1);
    if (!arg)
        return NULL;
    // Copier l’argument
    int j = 0;
    int start_i = *i - word_len;
    while (j < word_len)
    {
        arg[j] = s[start_i + j];
        j++;
    }
    arg[word_len] = '\0';
    // Sauter le guillemet fermant si présent
    if (quoted && s[*i] == quote_char)
        (*i)++;
    return (arg);
}

/*
** Découpe la chaîne en arguments.
** Retourne un tableau de chaînes terminé par NULL.
*/
static char **get_args(char *s, t_data *d)
{
    int i = 0;
    int k = 0;
    int len = ft_strlen(s);
    char **argv = malloc(sizeof(char *) * (len + 1));
    if (!argv)
        return NULL;

    while (s[i])
    {
        char *raw_arg = get_one_arg(s, &i);
        if (!raw_arg)
            break;
        char *arg = replace_envvar(raw_arg, d);
        free(raw_arg);
        if (!arg)
            break;
        argv[k++] = arg;
    }
    argv[k] = NULL;
    return argv;
}
#define commands_count 10

char ***split_commands(char **argv)
{
    char ***cmds = malloc(sizeof(char **) * (commands_count + 1));
    if (!cmds)
        return NULL;

    int i = 0, cmds_i = 0, arg_i = 0;
    cmds[cmds_i] = malloc(sizeof(char *) * (commands_count + 1));
    if (!cmds[cmds_i])
        return NULL;

    while (argv[i])
    {
        if (argv[i][0] == PIPE && argv[i][1] == '\0') // pipe isolé
        {
            cmds[cmds_i][arg_i] = NULL; // terminer la commande
            cmds_i++;
            arg_i = 0;
            cmds[cmds_i] = malloc(sizeof(char *) * (commands_count + 1));
            if (!cmds[cmds_i])
                return NULL;
        }
        else
        {
            cmds[cmds_i][arg_i] = argv[i];
            arg_i++;
        }
        i++;
    }
    cmds[cmds_i][arg_i] = NULL; // terminer la dernière commande
    cmds[cmds_i + 1] = NULL;    // terminer le tableau de commandes
    return cmds;
}


static char **split(t_data *d)
{
    char **argv = get_args(d->input, d);
    if (!argv)
        return (NULL);
    return (argv);
}

static int is_valid_bin(char *str)
{
    char *bin = ft_strdup(ft_strjoin("/bin/", str));
    int fd = open(bin, O_RDONLY);
    if (fd < 0)
        return (0);
    return (1);
}
// JE VEUX ***COMMANDS, qui contient des **INPUT_SPLITTED et *INPUT
// SO WHILE (COMMANDS[i])
    // run(commands[i]) link to commands[i] if | < > tu captes le delire
int filter_input(t_data *d, char *envp[])
{
    // RETURN 1 SEULEMENT SI ON VEUX TOUT EXIT
    if (d->input == NULL)
        return (1);

    if (count_quotes(d->input) % 2 != 0 || count_big_quotes(d->input) % 2 != 0)
    {
        print_error("Open quote not allowed: ", d->input);
        return (1);
    }
    d->input_splitted = split(d);
    if (d->input_splitted == NULL)
        return (1);
     
        //print_error("Command not found: ", d->input_splitted[0]);
    else if (check_command(d->input_splitted) == 1)
    {
        if (run_custom_cmd(d) == 1)
            return (1);
    }
    else if (check_command(d->input_splitted) == 0)
    {
        if (is_valid_bin(d->input_splitted[0]) == 1)
        {
            if (run_build_cmd(d, envp) == 1)
                return (1);
        }
        else
            print_error("command not found: ", d->input_splitted[0]);
    }
    return (0);
}
