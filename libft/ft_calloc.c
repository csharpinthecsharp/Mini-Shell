/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:47:15 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:08:13 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			tot;
	unsigned char	*ptr;
	size_t			i;

	if (nmemb && ((size_t)-1) / nmemb < size)
	{
		return (NULL);
	}
	tot = nmemb * size;
	ptr = malloc(tot);
	i = 0;
	if (!ptr)
	{
		return (NULL);
	}
	while (i < tot)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

/*
#include <stdio.h>

int	main(void)
{
	int	i;
	int	*allocate;

	i = 0;
	allocate = (int *)ft_calloc(5, sizeof(int));
	if (!allocate)
	{
		printf("Allocation failed.\n");
		return (1);
	}
	while (i < 5)
	{
		printf("allocate[%d] = %d\n", i, allocate[i]);
		i++;
	}
	free(allocate);
	return (0);
}
*/
