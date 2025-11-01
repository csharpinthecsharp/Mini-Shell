/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:46:38 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:43:34 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src && n > 0)
	{
		return (NULL);
	}
	i = 0;
	if (((unsigned char *)dest) > ((unsigned char *)src))
	{
		i = n;
		while (i > 0)
		{
			((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/*
#include <stdio.h>

int	main(void)
{
	char	dest[10];
	char	destover[10] = "fiifezf";
	char	src[10] = "test";

	ft_memmove(dest, src, 3);
	printf("Memmove basic -> %s\n", dest);
	ft_memmove(destover, src, 3);
	printf("Memove overlap -> %s\n", destover);
}
*/
