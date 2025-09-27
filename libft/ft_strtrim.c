/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:23:11 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:08:47 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_equal(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len1;
	size_t	len2;
	char	*dup;

	if (!s1 || !set)
		return (NULL);
	len1 = 0;
	len2 = ft_strlen(s1);
	while (s1[len1] && ft_is_equal(s1[len1], set))
	{
		len1++;
	}
	while (len2 > len1 && ft_is_equal(s1[len2 - 1], set))
	{
		len2--;
	}
	dup = malloc((sizeof(char) * (len2 - len1) + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1 + len1, len2 - len1 + 1);
	return (dup);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*s1;
	char	*set;
	char	*result;

	s1 = "abcHelloabc";
	set = "abc";
	result = ft_strtrim(s1, set);
	if (result)
	{
		printf("Before -> %s\n", s1);
		printf("After -> %s\n", result);
		free(result);
	}
	else
	{
		printf("Allocation error.\n");
	}
	return (0);
}
*/
