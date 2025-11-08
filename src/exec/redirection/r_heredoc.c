/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:16:18 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/08 12:17:59 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	init_heredoc_ctx(t_heredoc_ctx *ctx, t_data *d, int *pos,
		int index)
{
	ctx->d = d;
	ctx->delimiter = ft_strdup(d->cmd[*pos].arguments[index].file);
	ctx->should_expand = !d->cmd[*pos].arguments[index].heredoc_quoted;
	ctx->fd[0] = -1;
	ctx->fd[1] = -1;
	ctx->stdin_backup = -1;
	if (pipe(ctx->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ctx->stdin_backup = dup(STDIN_FILENO);
	if (ctx->stdin_backup != -1)
		return ;
	perror("dup");
	if (ctx->fd[0] >= 0)
		close(ctx->fd[0]);
	if (ctx->fd[1] >= 0)
		close(ctx->fd[1]);
	ctx->fd[0] = -1;
	ctx->fd[1] = -1;
}

static void	child_heredoc(t_heredoc_ctx *ctx)
{
	int	status;

	if (ctx->fd[0] >= 0)
		close(ctx->fd[0]);
	if (ctx->stdin_backup >= 0)
		close(ctx->stdin_backup);
	signal(SIGINT, heredoc_ctrl_c);
	status = heredoc_read_loop(ctx->fd[1], ctx->delimiter, ctx->d,
			ctx->should_expand);
	if (ctx->fd[1] >= 0)
		close(ctx->fd[1]);
	free(ctx->delimiter);
	exit(status);
}

static void	parent_handle(t_heredoc_ctx *ctx, pid_t pid, int is_last)
{
	int	status;
	int	interrupted;

	if (ctx->fd[1] >= 0)
		close(ctx->fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	interrupted = (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT);
	if (heredoc_parent_should_abort(ctx, status, interrupted))
		return ;
	signal(SIGINT, handler_ctrl_c);
	if (is_last && ctx->fd[0] >= 0 && dup2(ctx->fd[0], STDIN_FILENO) != -1)
		ctx->d->stdin_back = ctx->stdin_backup;
	else if (ctx->stdin_backup >= 0)
		close(ctx->stdin_backup);
	if (ctx->fd[0] >= 0)
		close(ctx->fd[0]);
}

void	heredoc(t_data *d, int *pos, int i, int is_last)
{
	t_heredoc_ctx	ctx;
	pid_t			pid;

	init_heredoc_ctx(&ctx, d, pos, i);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (ctx.fd[0] >= 0)
			close(ctx.fd[0]);
		if (ctx.fd[1] >= 0)
			close(ctx.fd[1]);
		if (ctx.stdin_backup >= 0)
			close(ctx.stdin_backup);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_heredoc(&ctx);
	parent_handle(&ctx, pid, is_last);
	free(ctx.delimiter);
}
