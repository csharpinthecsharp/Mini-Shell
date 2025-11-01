/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 23:09:31 by ltrillar          #+#    #+#             */
/*   Updated: 2025/07/28 12:27:32 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_format_dispatch(char c, va_list args, int *count)
{
	if (c == 'c')
		ft_cprint(args, count);
	else if (c == 's')
		ft_sprint(args, count);
	else if (c == '%')
		ft_prcprint(count);
	else if (c == 'i' || c == 'd')
		ft_iprint(args, count);
	else if (c == 'u')
		ft_uprint(args, count);
	else if (c == 'p')
		ft_pprint(args, count);
	else if (c == 'x')
		ft_xprint(args, count);
	else if (c == 'X')
		ft_xbigprint(args, count);
}

void	ft_checkformat(const char *f, va_list args, int *count)
{
	int	i;

	i = 0;
	while (f[i])
	{
		if (f[i] == '%' && f[i + 1])
			ft_format_dispatch(f[++i], args, count);
		else
		{
			ft_putchar_fd(f[i], 1);
			(*count)++;
		}
		i++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	ft_checkformat(format, args, &count);
	va_end(args);
	return (count);
}

/*
#include <stdio.h>

int	main(void)
{
	char	test;

	test = 10;
	// %c : caractère
	ft_printf("(Custom C) Bonjour lui c'est -> %c | Il est cool!\n", 'a');
	printf("(Default C) Bonjour lui c'est -> %c | Il est cool!\n", 'a');
	// %s : chaîne de caractères
	ft_printf("(Custom S) Bonjour lui c'est -> %s | Il est cool!\n", "Jean");
	printf("(Default S) Bonjour lui c'est -> %s | Il est cool!\n", "Jean");
	// %% : afficher un pourcentage
	ft_printf("(Custom per) Bonjour lui c'est -> %% | Il est cool!\n");
	printf("(Default per) Bonjour lui c'est -> %% | Il est cool!\n");
	// %i / %d : entier signé
	ft_printf("(Custom int base 10) Bonjour lui c'est -> %i | Il est cool!\n",
		1324);
	printf("(Default int base 10) Bonjour lui c'est -> %i | Il est cool!\n",
		1324);
	// %u : entier non signé
	ft_printf("(Custom U) Bonjour lui c'est -> %u | Il est cool!\n", -42);
	printf("(Default U) Bonjour lui c'est -> %u | Il est cool!\n", -42);
	// %d : entier signé
	ft_printf("(Custom d) Bonjour lui c'est -> %d | Il est cool!\n", 132);
	printf("(Default d) Bonjour lui c'est -> %d | Il est cool!\n", 132);
	// %p : pointeur
	ft_printf(" %p %p \n", 0, 0);
	printf(" %p %p \n", 0, 0);
	printf("x -> %x\n", test);
	printf("X -> %X\n", test);
	ft_printf("(Custom p) Bonjour lui c'est -> %x | Il est cool!\n", test);
	ft_printf("(Custom p) Bonjour lui c'est -> %X | Il est cool!\n", test);
	return (0);
}
*/
