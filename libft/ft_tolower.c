/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:47:13 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:08:50 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c += 32;
		return (c);
	}
	return (c);
}

/*
#include <stdio.h>

int	main(void)
{
	int	c;

	c = 'A';
	printf("ASCII Alphabetic -> %d | Char -> %c", ft_tolower(c), ft_tolower(c));
}
*/
