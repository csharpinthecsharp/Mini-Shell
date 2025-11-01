/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:18:18 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:08:16 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	int	c;
	int	cc;

	c = 55;
	cc = 128;
	printf("ASCII char -> %d\n", ft_isascii(c));
	printf("Non ASCII char -> %d", ft_isascii(cc));
}
*/
