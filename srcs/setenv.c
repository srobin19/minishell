/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:50:04 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 21:15:28 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				init_and_free(char ***roam, char ***environ, char **sub)
{
	*sub = NULL;
	*roam = *environ;
}

static char			**add_env(char ***environ, char *arg, char *arg2)
{
	char			**roam;
	char			**result;
	char			*str;
	char			*sub;

	init_and_free(&roam, environ, &sub);
	while (*roam)
	{
		sub_my_env(&sub, *roam);
		if (ft_strnequ(*roam, arg, ft_strlen(sub)))
		{
			ft_strdel(&sub);
			swap_env(&(*roam), arg, arg2);
			return (*environ);
		}
		ft_strdel(&sub);
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

static int			check_alpha(char **args)
{
	if (!args)
		return (0);
	if (!(ft_isalnum(args[1][0])))
	{
		ft_putendl("setenv: Variable name must begin with a letter.");
		return (0);
	}
	if (!(ft_stralpha(args[1])))
	{
		ft_putendl("setenv: Variable name must contain alphanum chars");
		return (0);
	}
	return (1);
}

static int			setenv_two_args(char ***environ, char **args)
{
	if (!check_alpha(args))
		return (0);
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
		return (ft_env(*environ));
	else if (ft_tablen(args) == 2)
	{
		setenv_two_args(environ, args);
		return (1);
	}
	else if (ft_tablen(args) > 3)
		ft_putendl("setenv: Too many arguments");
	else if (ft_tablen(args) == 3)
	{
		if (!check_alpha(args))
			return (1);
		*environ = add_env(environ, args[1], args[2]);
		return (1);
	}
	return (0);
}
