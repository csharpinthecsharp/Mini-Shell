/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:13:46 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 16:43:54 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/template.h"

char	*getpath(char *buffer, t_data *d)
{
	if (!getcwd(buffer, 1024))
		return (NULL);
	if (d->new_path == NULL)
		return (ft_strdup(buffer));
	return (ft_strjoin(buffer, d->new_path));
}

char	*get_promptpath(t_data *d)
{
	char	*trimmed;
	char	*prompt;
	int		i;
	int		j;

	trimmed = ft_strdup(d->path);
	if (!trimmed)
		return (NULL);
	i = ft_strlen(trimmed);
	while (i > 0 && trimmed[i - 1] != '/')
		i--;
	prompt = malloc(sizeof(char) * (ft_strlen(trimmed) - i + 1));
	if (!prompt)
		return (free(trimmed), NULL);
	j = 0;
	while (trimmed[i])
		prompt[j++] = trimmed[i++];
	prompt[j] = '\0';
	free(trimmed);
	trimmed = ft_strjoin(TEMPLATE_PROMPT, prompt);
	free(prompt);
	if (!trimmed)
		return (NULL);
	prompt = ft_strjoin(trimmed, TEMPLATE_PROMPT_END);
	return (free(trimmed), prompt);
}
