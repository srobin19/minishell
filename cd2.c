/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 21:35:15 by srobin            #+#    #+#             */
/*   Updated: 2019/10/07 22:24:26 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_cd(char **args)
{
	if (ft_tablen(args) == 3)
	{
		ft_putstr("cd: String not in pwd: ");
		ft_putendl(args[1]);
		return (0);
	}
	else if (ft_tablen(args) > 3)
	{
		ft_putendl("cd: Too many arguments.");
		return (0);
	}
	return (1);
}

int				cd_back(char ***environ, char **args, char *oldpath)
{
	char		buf[4096];

	if (!oldpath)
		return (0);
	if (ft_tablen(args) == 1)
		return (0);
	if (!args[1])
		return (0);
	if (!(ft_strcmp(args[1], "-")))
	{
		set_oldpwd_env(environ, getcwd(buf, 4096), 1);
		if (chdir(oldpath))
			return (0);
		set_pwd_env(environ);
		return (1);
	}
	return (0);
}
