/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:10:37 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:08:22 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*spoint1 = (const unsigned char *)s1;
	const unsigned char	*spoint2 = (const unsigned char *)s2;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (spoint1[i] != spoint2[i])
		{
			return (spoint1[i] - spoint2[i]);
		}
		i++;
	}
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*s1;
	char	*s2;
	int		result;

	s1 = "qeeq";
	s2 = "veeqa";
	result = ft_memcmp(s1, s2, 3);
	printf("%d", result);
	return (0);
}
*/
