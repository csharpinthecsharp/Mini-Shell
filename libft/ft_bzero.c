/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:45:43 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:16:00 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

/*
#include <stdio.h>

int	main(void)
{
	char	str[10] = "abcdefg";
	int		i;

	// we initialize str[] with 10 octet.
	// we ask bzero, hey ? can you remove 5 octet ?
	ft_bzero(str, 5);
	i = 0;
	// for each octet of str[] wich one is equal to '\0' ?
	// 0 would mean that they are erased or where not containing anything
	//
	while (i < 10)
	{
		// %d (str[i]) is the ASCII of a, b, c etc...
		printf("octet -> %d | %d)\n", i, str[i]);
		i++;
	}
}
*/
