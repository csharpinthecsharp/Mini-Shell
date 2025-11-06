/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_pre_exec_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:25:22 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/25 14:52:56 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_error	*create_error_node(int exit_code, const char *message,
					const char *argument)
{
	t_error	*node;

	node = malloc(sizeof * node);
	if (!node)
		return (NULL);
	node->message = ft_strdup(message);
	if (!node->message)
	{
		free(node);
		return (NULL);
	}
	node->argument = ft_strdup(argument);
	if (!node->argument)
	{
		free(node->message);
		free(node);
		return (NULL);
	}
	node->exit_code = exit_code;
	node->next = NULL;
	return (node);
}

void	add_deferred_error(t_data *d, int exit_code, const char *message,
			const char *argument)
{
	t_error	*node;
	t_error	*tail;

	if (!d)
		return ;
	node = create_error_node(exit_code, message, argument);
	if (!node)
	{
		print_error(message, argument);
		return ;
	}
	if (!d->errors)
		d->errors = node;
	else
	{
		tail = d->errors;
		while (tail->next)
			tail = tail->next;
		tail->next = node;
	}
}

void	flush_deferred_errors(t_data *d)
{
	t_error	*node;

	if (!d)
		return ;
	while (d->errors)
	{
		node = d->errors;
		d->errors = node->next;
		print_error(node->message, node->argument);
		free(node->message);
		free(node->argument);
		free(node);
	}
}

void	clear_deferred_errors(t_data *d)
{
	t_error	*node;

	if (!d)
		return ;
	while (d->errors)
	{
		node = d->errors;
		d->errors = node->next;
		free(node->message);
		free(node->argument);
		free(node);
	}
}

void	set_error(t_data *d, int exit_code, char *error_s, char *tmp)
{
	d->exit_status = exit_code;
	if (d->defer_errors)
		add_deferred_error(d, exit_code, error_s, tmp);
	else
		print_error(error_s, tmp);
}
