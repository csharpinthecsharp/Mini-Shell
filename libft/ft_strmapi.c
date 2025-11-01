/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:55:19 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:30:03 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s1;
	size_t	i;
	size_t	len;

	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len])
	{
		len++;
	}
	s1 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s1)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s1[i] = f(i, s[i]);
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
/*
#include <stdio.h>

char	ft_ttolower(unsigned int i, char c)
{
	(void)i;
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}


int	main(void)
{
	char	str[] = "HELLO WORLD";
	char	*result;

	result = ft_strmapi(str, ft_ttolower);
	if (result)
	{
		printf("Original: %s\n", str);
		printf("Modified: %s\n", result);
		free(result);
	}
	else
	{
		printf("Memory allocation failed.\n");
	}
	return (0);
}
*/
