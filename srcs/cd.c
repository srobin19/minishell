/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 21:07:30 by srobin            #+#    #+#             */
/*   Updated: 2019/10/07 23:26:48 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				set_oldpwd_env(char ***environ, char *oldpath, int opt)
{
	char		**roam;
	char		*newpath;
	char		buf[4096];

	if (!*environ)
		return (0);
	roam = *environ;
	while (*roam)
	{
		if (ft_strnstr(*roam, "OLDPWD=", 7))
		{
			newpath = getcwd(buf, 4096);
			if (ft_strcmp(oldpath, newpath) || opt)
				swap_env(&(*roam), "OLDPWD", oldpath);
			return (1);
		}
		roam++;
	}
	return (0);
}

int				set_pwd_env(char ***environ)
{
	char		**roam;
	char		buf[4096];

	if (!*environ)
		return (0);
	roam = *environ;
	while (*roam)
	{
		if (*roam && ft_strnstr(*roam, "PWD=", 4))
		{
			swap_env(&(*roam), "PWD", getcwd(buf, 4096));
			return (1);
		}
		roam++;
	}
	return (0);
}

static int		reset_cd(char ***environ, char *oldpath)
{
	char		**roam;
	char		*home;

	if (!*environ)
		return (0);
	roam = *environ;
	while (*roam)
	{
		if (ft_strnstr(*roam, "HOME=", 5))
		{
			if (!(home = ft_strsub(*roam, 5, ft_strlen(*roam))))
				exit(EXIT_FAILURE);
			if (chdir(home))
			{
				ft_putendl("cd: HOME not set..");
				return (-1);
			}
			set_oldpwd_env(environ, oldpath, 0);
			set_pwd_env(environ);
			ft_strdel(&home);
			return (1);
		}
		roam++;
	}
	return (0);
}

static int		access_right(char *path)
{
	struct stat	buf;

	if (!stat(path, &buf))
	{
		if (access(path, R_OK))
		{
			cd_msg(path);
			ft_putendl(": Permissions denied.");
			return (-1);
		}
		if (!S_ISDIR(buf.st_mode))
		{
			cd_msg(path);
			ft_putendl(": Not a directory.");
			return (-1);
		}
	}
	if (chdir(path))
	{
		cd_msg(path);
		ft_putendl(": No such file or directory.");
		return (-1);
	}
	return (1);
}

int				ft_cd(char **environ, char **args)
{
	char		buf[4096];
	static char	*oldpath;

	if (!args || !environ)
		return (0);
	if (!check_cd(args))
		return (-1);
	if ((cd_back(&environ, args, oldpath)))
		return (1);
	oldpath = getcwd(buf, 4096);
	if (ft_tablen(args) == 1 || !(ft_strcmp(args[1], "--")))
		return (reset_cd(&environ, oldpath));
	if (!access_right(args[1]))
		return (-1);
	set_oldpwd_env(&environ, oldpath, 0);
	set_pwd_env(&environ);
	return (1);
}
