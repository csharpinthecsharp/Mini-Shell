/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:45:30 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/17 16:25:33 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	char	c;
	char	cc;

	c = '5';
	cc = 'a';
	printf("Digit char -> %d\n", ft_isdigit(c));
	printf("Non digit char -> %d", ft_isdigit(cc));
}
*/
