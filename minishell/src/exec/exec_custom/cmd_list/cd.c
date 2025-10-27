/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:38:38 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/27 16:52:29 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static int	refresh_path(t_data *d)
{
	char	*cwd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd failed");
		return (FAILED);
	}
	int i = 0;
	char *temp;
	char *pwd;
	
	while (d->envp[i])
	{
		if (ft_strncmp(d->envp[i], "PWD=", 4) == 0)
		{
			int j = 0;
			temp = strdup(d->envp[i]);
			while (temp[j] != '=')
				j++;
			j++;
			pwd = ft_strdup(cwd);
			free(d->envp[i]);
			d->envp[i] = malloc(sizeof(char *) * ft_strlen(pwd));
			d->envp[i] = ft_strjoin("PWD=", pwd);
		}
		else if (ft_strncmp(d->envp[i], "OLDPWD=", 7) == 0)
		{
			int k = 0;
			temp = strdup(d->envp[i]);
			while (temp[k] != '=')
				k++;
			k++;
			free(d->envp[i]);
			d->envp[i] = malloc(sizeof(char *) * ft_strlen(d->path + 7));
			d->envp[i] = ft_strjoin("OLDPWD=", d->path);
			printf("old envp i = %s\n", d->envp[i]);
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
