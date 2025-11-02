/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:47:19 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:08:51 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c -= 32;
		return (c);
	}
	return (c);
}

/*
#include <stdio.h>

int	main(void)
{
	int	c;

	c = 'a';
	printf("ASCII Alphabetic -> %d | Char -> %c\n", ft_toupper(c),
		ft_toupper(c));
}
*/
