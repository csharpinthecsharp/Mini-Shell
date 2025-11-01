/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:00:33 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:42:33 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	if ((!little && len == 0) || (!big && len == 0))
		return (NULL);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] != '\0' && i + j < len && big[i + j] == little[j])
		{
			j++;
		}
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	const char *big =  "Je suis en train de manger";
	const char *little = "en train";
	const char *littley = "Il ne mange pas";

	char *result = strnstr(big, little, 30);
	char *resulti = strnstr(big, little, 5);
	char *resultj = strnstr(big, littley, 30);

		// Len is good and little also, will return
		// en train de manger
	printf("Len 30 && identic start -> %s\n", result);

	// Little is greater than big, then return NULL.
	printf("Len 5 && identic start -> %s\n", resulti);

	// No match, will return NULL
	printf("Len 30 && not identic -> %s\n", resultj);
}*/
