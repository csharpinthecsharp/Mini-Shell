/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:48:29 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:08:38 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	n;
	unsigned int	dlen;
	unsigned int	slen;

	slen = ft_strlen(src);
	if (!dest && size == 0)
	{
		return (slen);
	}
	dlen = ft_strlen(dest);
	if (size <= dlen)
	{
		return (size + slen);
	}
	n = dlen;
	dest += n;
	while (n < size - 1 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		n++;
	}
	*dest = '\0';
	return (dlen + slen);
}
/*
#include <stdio.h>

int	main(void)
{
	char	cat[4] = "Meow";

	ft_strlcat(cat, " Meooow", 8);
	printf("%s", cat);
	return (0);
}
*/
