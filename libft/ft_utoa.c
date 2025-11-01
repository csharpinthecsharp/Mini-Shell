/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:33:49 by ltrillar          #+#    #+#             */
/*   Updated: 2025/08/24 13:16:40 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(unsigned int n)
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
