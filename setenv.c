/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:50:04 by srobin            #+#    #+#             */
/*   Updated: 2019/10/07 17:05:21 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void				swap_env(char **environ, char *arg, char *arg2)
{
	if (!environ || !arg)
		return ;
	free(*environ);
	if (!(*environ = ft_strjoin3(arg, "=", arg2)))
		exit(EXIT_FAILURE);
}

static char			**add_env(char ***environ, char *arg, char *arg2)
{
	char			**roam;
	char			**result;
	char			*str;

	if (!environ || !arg)
		return (0);
	roam = *environ;
	while (*roam)
	{
		if (ft_strnstr(*roam, arg, ft_strlen(arg)))
		{
			swap_env(&(*roam), arg, arg2);
			return (*environ);
		}
		roam++;
	}
	if (!(str = ft_strjoin3(arg, "=", arg2)))
		exit(EXIT_FAILURE);
	if (!(result = ft_tabstradd(*environ, str)))
		exit(EXIT_FAILURE);
	free(str);
	ft_tabfree(environ);
	return (result);
}

static int			setenv_two_args(char ***environ, char **args)
{
	if (!ft_isalnum(args[1][0]))
	{
		ft_putendl("setenv: Variable name must begin with a letter.");
		return (0);
	}
	else if (!ft_stralpha(args[1]))
	{
		ft_putendl("setenv: Variable name must contain alphanumeric characters.");
		return (0);
	}
	else
	{
		*environ = add_env(environ, args[1], NULL);
		return (1);
	}
	return (0);
}

int					ft_setenv(char ***environ, char **args)
{
	if (!environ || !args)
		return (0);
	if (ft_tablen(args) < 2)
		ft_env(*environ);
	else if (ft_tablen(args) == 2)
	{
		setenv_two_args(environ, args);
		return (1);
	}
	else if (ft_tablen(args) > 3)
		ft_putendl("setenv: Too many arguments");
	else if (ft_tablen(args) == 3)
	{
		*environ = add_env(environ, args[1], args[2]);
		return (1);
	}
	return (0);
}