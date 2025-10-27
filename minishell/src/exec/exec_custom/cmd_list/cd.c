/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:38:38 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/27 19:10:32 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static int	refresh_path(t_data *d)
{
	char	*cwd;
	char	*pwd;
	char	*temp;
	int		i;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd failed");
		return (FAILED);
	}

	i = 0;
	while (d->envp[i])
	{
		if (ft_strncmp(d->envp[i], "PWD=", 4) == 0)
		{
			temp = d->envp[i];
			pwd = ft_strjoin("PWD=", cwd);
			d->envp[i] = pwd;
			free(temp);
		}
		else if (ft_strncmp(d->envp[i], "OLDPWD=", 7) == 0)
		{
			temp = d->envp[i];
			if (d->path)
				d->envp[i] = ft_strjoin("OLDPWD=", d->path);
			else
				d->envp[i] = ft_strdup("OLDPWD=");
			free(temp);
		}
		i++;
	}

	if (d->path)
		free(d->path);
	d->path = cwd;
	return (SUCCESS);
}


static char	*get_home(t_data *d)
{
	char	*home;

	home = ft_get_env(d, "HOME");
	if (!home)
	{
		d->exit_status = 1;
		print_error("HOME not set", "cd");
		return (NULL);
	}
	return (home);
}

int	handle_cd(char **argv, int count, t_data *d)
{
	char	*target;

	target = NULL;
	if (count == 1)
		target = get_home(d);
	else if (count == 2)
		target = argv[1];
	else
		return (print_error("too many arguments", argv[0]), FAILED);
	if (!target)
		return (FAILED);
	if (chdir(target) != 0)
		return (print_error("No such file or directory", argv[0]), FAILED);
	if (refresh_path(d) == FAILED)
		return (FAILED);
	return (SUCCESS);
}
