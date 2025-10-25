/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_pre_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:47:20 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/24 17:05:52 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_directory(const char *path)
{
	int		len;
	int		i;
	char	*dir;

	len = ft_strlen(path);
	i = len - 1;
	while (i >= 0 && path[i] != '/')
		i--;
	if (i < 0)
		return (strdup("."));
	dir = malloc(i + 1);
	if (!dir)
		return (NULL);
	strncpy(dir, path, i);
	dir[i] = '\0';
	return (dir);
}

int	count_redir_arg(t_cmd *cmd)
{
	int	i;
	int	arg_count;

	arg_count = 0;
	i = 0;
	while (i < cmd->nb_arg)
	{
		if ((!ft_strncmp(cmd->arg[i], ">>", 3) || !ft_strncmp(cmd->arg[i], "<<",
					3) || !ft_strncmp(cmd->arg[i], ">", 2)
				|| !ft_strncmp(cmd->arg[i], "<", 2)) && cmd->arg[i + 1])
		{
			i += 2;
		}
		else
		{
			arg_count++;
			i++;
		}
	}
	return (arg_count);
}

int	is_redir_and_next(char **argv, int i)
{
	if ((!ft_strncmp(argv[i], ">>", 3) || !ft_strncmp(argv[i], "<<", 3)
			|| !ft_strncmp(argv[i], ">", 2) || !ft_strncmp(argv[i], "<", 2))
		&& argv[i + 1])
		return (SUCCESS);
	return (FAILED);
}
char	**fix_redir_arg(t_cmd *cmd)
{
	int		i;
	int		arg_count;
	int		arg_j;
	char	**dup;

	i = 0;
	arg_j = 0;
	arg_count = count_redir_arg(cmd);
	dup = malloc(sizeof(char *) * (arg_count + 1));
	if (!dup)
		return (NULL);
	while (i < cmd->nb_arg)
	{
		if (is_redir_and_next(cmd->arg, i) == SUCCESS)
		{
			i += 2;
			continue ;
		}
		dup[arg_j++] = ft_strdup(cmd->arg[i]);
		i++;
	}
	dup[arg_j] = NULL;
	cmd->nb_arg = arg_count;
	return (dup);
}

static void	set_error(t_data *d, int exit_code, char *error_s, char *tmp)
{
	d->exit_status = exit_code;
	print_error(error_s, tmp);
}

static int	stat_error_h(t_data *d, char *tmp)
{
	struct stat	st;

	if (stat(tmp, &st) == -1)
	{
		if (errno == ENOENT && ft_strchr(tmp, '/') != NULL)
			set_error(d, 127, "No such file or directory", tmp);
		else if (errno == EACCES)
			set_error(d, 126, "Permission denied", tmp);
		else
			set_error(d, 127, "command not found", tmp);
		return (FAILED);
	}
	if (S_ISDIR(st.st_mode))
	{
		if (ft_strchr(tmp, '/') != NULL)
			set_error(d, 126, "Is a directory", tmp);
		else
			set_error(d, 127, "command not found", tmp);
		return (FAILED);
	}
	return (SUCCESS);
}

static int	error_h(t_data *d, char *tmp)
{
	if (ft_strchr(tmp, '/') == NULL)
	{
		set_error(d, 127, "command not found", tmp);
		return (FAILED);
	}
	if (stat_error_h(d, tmp) == FAILED)
		return (FAILED);
	if (access(tmp, X_OK) != 0)
	{
		if (errno == EACCES)
			set_error(d, 126, "Permission denied", tmp);
		else
			set_error(d, 127, "command not found", tmp);
		return (FAILED);
	}
	return (SUCCESS);
}

int	put_cmdstate(int type, int *is_stateful, t_cmd *cmd, t_data *d)
{
	char	*tmp;

	if (check_non_bin(cmd, type, is_stateful, d) == FAILED)
		return (FAILED);
	else if (type == BIN)
	{
		tmp = ft_strdup(cmd->arg[0]);
		if (is_available(tmp, d) == SUCCESS)
		{
			cmd->state_cmd = BIN;
			free(tmp);
		}
		else
		{
			if (error_h(d, tmp) == FAILED)
			{
				free(tmp);
				return (FAILED);
			}
		}
	}
	return (SUCCESS);
}
