/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:01:53 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:08:14 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
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
	char	ccc;

	c = 'a';
	cc = '5';
	ccc = '$';
	printf("Alpha char -> %d\n", ft_isalnum(c));
	printf("Digit char -> %d\n", ft_isalnum(cc));
	printf("Non Alphar/Digit -> %d", ft_isalnum(ccc));
}
*/
