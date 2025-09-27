/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:25:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/07/28 12:27:45 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Affiche un caractère passé en argument variadique
void	ft_cprint(va_list args, int *count)
{
	char	c;

	c = (char)va_arg(args, int);
	ft_putchar_fd(c, 1);
	(*count)++;
}

void	ft_sprint(va_list args, int *count)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		*count += 6;
		return ;
	}
	ft_putstr_fd(str, 1);
	*count += ft_strlen(str);
}

void	ft_prcprint(int *count)
{
	ft_putchar_fd('%', 1);
	(*count)++;
}

void	ft_iprint(va_list args, int *count)
{
	int		n;
	char	*result;

	n = va_arg(args, int);
	result = ft_itoa(n);
	ft_putstr_fd(result, 1);
	*count += ft_strlen(result);
	free(result);
}

void	ft_uprint(va_list args, int *count)
{
	unsigned int	n;
	char			*result;

	n = va_arg(args, unsigned int);
	result = ft_utoa(n);
	ft_putstr_fd(result, 1);
	*count += ft_strlen(result);
	free(result);
}
