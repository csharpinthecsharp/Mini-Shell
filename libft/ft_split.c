/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:17:16 by ltrillar          #+#    #+#             */
/*   Updated: 2025/08/24 12:50:25 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	*ft_word_alloc(const char *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

void	ft_free(char **res, int count)
{
	while (--count >= 0)
		free(res[count]);
	free(res);
}

int	ft_write_word(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	start;
	int		word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			tab[word] = ft_word_alloc(s, start, i);
			if (!tab[word])
				return (-1);
			word++;
		}
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		count;
	int		ret;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	ret = ft_write_word(tab, s, c);
	if (ret == -1)
	{
		ft_free(tab, ret);
		return (NULL);
	}
	tab[count] = NULL;
	return (tab);
}
