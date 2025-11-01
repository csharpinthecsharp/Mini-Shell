/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:31:14 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:27:44 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((char)c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

/*
#include <stdio.h>

int	main(void) {
	const char *str = "trouve moi";
	char c = 'o';

	char *occurence = ft_strchr(str, c);

	if (occurence) {
		printf("Occurence -> %c | Letter number -> %ld\n", c, occurence - str);
	}
	else
	{
			printf("No occurence found.");
	}
	return (0);
}
*/
