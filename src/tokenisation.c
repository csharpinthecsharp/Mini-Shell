/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/04 17:38:51 by ltrillar         ###   ########.fr       */
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
#include "../include/minishell.h"

static int ft_isspace(char arg)
{
    if (arg == ' ' || arg == '\t')
        return (1);
    return (0);
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
static char **get_args(char *s)
{
    int i = 0;
    int k = 0;
    int len = ft_strlen(s);
    char **argv = malloc(sizeof(char *) * (len + 1));
    if (!argv)
        return NULL;

    while (s[i])
    {
        char *arg = get_one_arg(s, &i);
        if (!arg)
            break;
        argv[k++] = arg;
    }
    argv[k] = NULL;
    return argv;
}

static int is_there_a_pipe(char **argv)
{
    int i = 0;
    int count = 0;
    while (argv[i])
    {
        if (argv[i][0] == PIPE)
            count++;
        i++;
    }
    return (count);
}

static char ***split_pipe(char **argv, t_data *d)
{
    int i = 0;
    int pipe_count = is_there_a_pipe(argv);
    d->commands = malloc(sizeof(char **) * BUFFER_SIZE);
    if (!d->commands)
        return (NULL);

    while (pipe_count > 0)
    {
        if (argv[i][0] == PIPE)
        {
            pipe_count--;
        }
        i++;
    }
    return (d->commands);
}

static char **split(t_data *d)
{
    char **argv = get_args(d->input);
    if (!argv)
        return (NULL);

    if (is_there_a_pipe(argv) > 0)
    {
        d->commands = split_pipe(argv, d);
        if (d->commands == NULL)
            return (NULL);
    }
    return (argv);
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
     
    if (check_command(d->input_splitted) == 0)
        print_error("Command not found: ", d->input_splitted[0]);
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
