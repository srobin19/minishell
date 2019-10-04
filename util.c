/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:04:24 by srobin            #+#    #+#             */
/*   Updated: 2019/10/05 01:45:44 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				execute_bin(char *path, char **args)
{
	pid_t		process;

	if (!path)
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

int				execute_builtin(char **environ, char **args)
{
	if (!args)
		return (0);
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(environ, args));
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(environ, args));
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(environ));
	else if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args));
	return (0);
}
