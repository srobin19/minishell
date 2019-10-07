/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 21:07:30 by srobin            #+#    #+#             */
/*   Updated: 2019/10/07 17:41:56 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_pwd_env(char ***environ, char *path)
{
	char		**roam;
	char		buf[4096];

	if (!environ || !path)
		return (0);
	roam = *environ;
	while (roam)
	{
		if (*roam && ft_strnstr(*roam, "PWD=", 4))
		{
			swap_env(&(*roam), "PWD", getcwd(buf, 4096));
			return (1);
		}
		roam++;
	}
	return (1);
}

static int		reset_cd(char **environ, char *path)
{
	if (!path || !environ)
		return (0);
	if (chdir(path))
	{
		ft_putendl("HOME is not defined in minishell.h.");
		return (-1);
	}
	set_pwd_env(&environ, path);
	return (1);
}

static int		access_right(char *path)
{
	if (!path)
		return (0);
	if (access(path, R_OK))
	{
		ft_putstr("cd: ");
		ft_putstr(path);
		ft_putendl(": Permissions denied.");
		return (0);
	}
	else
		return (1);
}
int				ft_cd(char **environ, char **args)
{
	if (!args || !environ)
		return (0);
	if (ft_tablen(args) == 3)
	{
		ft_putstr("cd: String not in pwd: ");
		ft_putendl(args[1]);
		return (-1);
	}
	else if (ft_tablen(args) > 3)
	{
		ft_putendl("cd: Too many arguments.");
		return (-1);
	}
	if (ft_tablen(args) == 1)
		return (reset_cd(environ, HOME));
	if (!access_right(args[1]))
		return (-1);
	else if (chdir(args[1]))
	{
		ft_putstr("cd: No such file or directory: ");
		ft_putendl(args[1]);
		return (-1);
	}
	set_pwd_env(&environ, args[1]);
	return (1);
}
