/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:04:24 by srobin            #+#    #+#             */
/*   Updated: 2019/10/04 19:31:54 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				execute(char *path, char **args, char *exe)
{
	pid_t		process;

	if (!path || !exe)
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
