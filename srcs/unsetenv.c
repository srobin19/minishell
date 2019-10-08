/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:32:37 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 21:15:37 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_args(char *environ, char **args)
{
	char *sub;

	sub = NULL;
	while (*args)
	{
		sub_my_env(&sub, environ);
		if (ft_strnequ(environ, *args, ft_strlen(sub)))
		{
			ft_strdel(&sub);
			return (1);
		}
		ft_strdel(&sub);
		args++;
	}
	return (0);
}

static char		**del_env(char ***environ, char **args, int size)
{
	char		**result;
	char		**result_ptr;
	char		**roam;
	size_t		i;

	if (!(result = (char**)malloc(sizeof(char*) *
	(ft_tablen(*environ) + 1 - size))))
		exit(EXIT_FAILURE);
	roam = *environ;
	result_ptr = result;
	i = 0;
	while (i < ft_tablen(*environ) - size)
	{
		if (!check_args(*roam, args))
		{
			if (!(*result_ptr = ft_strdup(*roam)))
				exit(EXIT_FAILURE);
			result_ptr++;
			i++;
		}
		roam++;
	}
	*result_ptr = NULL;
	ft_tabfree(environ);
	return (result);
}

static int		ft_args_match(char **environ, char **args)
{
	char		**roam;
	char		**args_ptr;
	int			result;
	char		*sub;

	sub = NULL;
	roam = environ;
	result = 0;
	while (*roam)
	{
		args_ptr = args;
		while (*args_ptr)
		{
			sub_my_env(&sub, *roam);
			if (ft_strnequ(*roam, *args_ptr, ft_strlen(sub)))
				result++;
			ft_strdel(&sub);
			args_ptr++;
		}
		roam++;
	}
	return (result);
}

int				ft_unsetenv(char ***environ, char **args)
{
	if (!environ || !args)
		return (0);
	if (ft_tablen(args) < 2)
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		*environ = del_env(environ, args, (ft_args_match(*environ, args)));
		return (1);
	}
	return (-1);
}
