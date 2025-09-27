/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:55:53 by ltrillar          #+#    #+#             */
/*   Updated: 2025/06/21 14:40:31 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*strrchr find the last occurence in the C char,
 * and return it to the pointer OR NULL if not found
 */
char	*ft_strrchr(const char *s, int c)
{
	const char	*occurence = NULL;

	while (*s)
	{
		if (*s == (char)c)
		{
			occurence = s;
		}
		s++;
	}
	if ((char)c == '\0')
	{
		return ((char *)s);
	}
	return ((char *)occurence);
}

/*
#include <stdio.h>

int	main(void) {
	const char *str = "trouve moi";
	char c = 'o';

	char *occurence = ft_strrchr(str, c);

	if (occurence) {
		printf("Occurence -> %c | Letter number -> %ld\n", c, occurence - str);
	}
	else
	{
		printf("No occurence found.");
	}
	return (0);
}
*/
