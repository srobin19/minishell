/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:04:24 by srobin            #+#    #+#             */
/*   Updated: 2019/10/07 17:34:25 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**env_cpy(char **environ)
{
	char		**result;
	char		**result_ptr;
	char		**roam;
	size_t		i;

	if (!*environ)
	{
		ft_putendl("minishell: env is NULL, please try again");
		exit(EXIT_FAILURE);
	}
	if (!(result = (char**)malloc(sizeof(char *) * (ft_tablen(environ) + 1))))
		exit(EXIT_FAILURE);
	roam = environ;
	result_ptr = result;
	i = 0;
	while (i < ft_tablen(environ))
	{
		if (!(*result_ptr = ft_strdup(*roam)))
			exit(EXIT_FAILURE);
		result_ptr++;
		roam++;
		i++;
	}
	*result_ptr = NULL;
	return (result);
}

int				execute_bin(char *path, char **args)
{
	pid_t		process;

	if (!path || !args)
		return (0);
	process = fork();
	if (process == 0)
	{
		execve(path, args, NULL);
		exit(EXIT_SUCCESS);
	}
	if (process > 0)
		wait(&process);
	if (process < 0)
	{
		ft_putstr(path);
		ft_putstr(": An error has occured\n");
	}
	return (1);
}

int				execute_builtin(char ***environ, char **args)
{
	if (!args || !environ)
		return (0);
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(*environ, args));
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(*environ, args));
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(*environ));
	else if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args));
	else if (!ft_strcmp(args[0], "setenv"))
		return (ft_setenv(environ, args));
	return (0);
}
