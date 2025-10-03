/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:20:05 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/04 00:30:33 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char **split(t_data *d)
{
    char **argv = get_args(d->input);  
    if (!argv)
        return (NULL);
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
