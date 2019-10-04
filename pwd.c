/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 22:36:34 by srobin            #+#    #+#             */
/*   Updated: 2019/10/05 01:45:58 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_pwd(char **environ, char **args)
{
	char		buf[4096];
	char		*path;

	if (!environ)
		return (0);
	if (ft_tablen(args) > 1)
	{
		ft_putendl("pwd: too many arguments");
		return (-1);
	}
	path = getcwd(buf, 4096);
	ft_putendl(path);
	return (1);
}
