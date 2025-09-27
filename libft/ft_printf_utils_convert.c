/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_convert.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:35:21 by ltrillar          #+#    #+#             */
/*   Updated: 2025/07/28 12:27:53 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_pprint(va_list args, int *count)
{
	void	*ptr;

	ptr = va_arg(args, void *);
	*count += ft_print_ptr((unsigned long long)ptr);
}

void	ft_xprint(va_list args, int *count)
{
	unsigned int	val;

	val = va_arg(args, unsigned int);
	*count += ft_print_hex(val, 0);
}

void	ft_xbigprint(va_list args, int *count)
{
	unsigned int	val;

	val = va_arg(args, unsigned int);
	*count += ft_print_hex(val, 1);
}
