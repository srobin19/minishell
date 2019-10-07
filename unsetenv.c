/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:32:37 by srobin            #+#    #+#             */
/*   Updated: 2019/10/07 22:43:04 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_args(char *environ, char **args)
{
	while (*args)
	{
		if (ft_strnstr(environ, *args, ft_strlen(*args)))
			return (1);
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

	roam = environ;
	result = 0;
	while (*roam)
	{
		args_ptr = args;
		while (*args_ptr)
		{
			if (ft_strnstr(*roam, *args_ptr, ft_strlen(*args_ptr)))
				result++;
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
	return (0);
}
