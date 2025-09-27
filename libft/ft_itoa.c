/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:20:06 by ltrillar          #+#    #+#             */
/*   Updated: 2025/07/28 12:25:55 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int_len(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	char	*result;
	int		i;

	nbr = n;
	len = ft_int_len(nbr);
	result = malloc(len + 1);
	i = len - 1;
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (nbr)
	{
		result[i--] = ((nbr % 10) + '0');
		nbr /= 10;
	}
	return (result);
}
/*
#include <stdio.h>

int	main(void)
{
	int		nbr;
	char	*result;

	nbr = -42;
	result = ft_itoa(nbr);
	if (result)
	{
		printf("%s", result);
		free(result);
	}
	return (0);
}
*/
