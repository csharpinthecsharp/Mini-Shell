/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:48:31 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:08:43 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' || s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - ((unsigned char)s2[i]));
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
	char	*s3;

	s1 = "aa";
	s2 = "aa";
	s3 = "aaa";
	printf("s1 & s2 -> %d\n", ft_strncmp(s1, s2, 10));
	printf("s3 & s1 -> %d\n", ft_strncmp(s3, s1, 20));
	printf("s1 & s3 -> %d\n", ft_strncmp(s1, s3, 20));
	return (0);
}
*/
