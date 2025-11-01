/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:32:22 by ltrillar          #+#    #+#             */
/*   Updated: 2025/07/28 12:15:01 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_hex(unsigned int num, int uppercase)
{
	char	*base;

	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (num >= 16)
	{
		ft_put_hex(num / 16, uppercase);
		ft_put_hex(num % 16, uppercase);
	}
	else
		ft_putchar_fd(base[num], 1);
}

int	ft_print_hex(unsigned int num, int uppercase)
{
	int				len;
	unsigned int	tmp;

	len = 0;
	tmp = num;
	if (num == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	while (tmp)
	{
		len++;
		tmp /= 16;
	}
	ft_put_hex(num, uppercase);
	return (len);
}
