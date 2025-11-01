/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:51:13 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:08:21 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
		{
			return ((void *)(ptr + i));
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void) {
	const char *str = "trouve moi";
	char c = 'o';

	char *occurencelimited = ft_memchr(str, c, 1);
	char *occurencenonlimited = ft_memchr(str, c, 5);

	if (occurencelimited) {
		printf("[LIM] Occ -> %c | Let nbr -> %ld\n", c, occurencelimited - str);
	}
	else
	{
			printf("[LIM] No occurence found.\n");
	}
	if (occurencenonlimited) {
	printf("[NONL] Occ -> %c | Let nbr -> %ld\n", c, occurencenonlimited - str);
	}
	else
	{
			printf("[NONL] No occurence found.\n");
	}
	return (0);
}
*/
