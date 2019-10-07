/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:14:07 by srobin            #+#    #+#             */
/*   Updated: 2019/10/05 23:53:18 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				**get_path_dir(char **environ)
{
	size_t		i;
	char		*path;
	char		**result;

	if (!*environ)
		return (NULL);
	i = 0;	
	while (environ[i])
	{
		if (environ[i] && ft_strnstr(environ[i], "PATH=", 5))
		{
			if (!(path = ft_strsub(environ[i], 5, ft_strlen(environ[i]))))
				exit(EXIT_FAILURE);
			if (!(result = ft_strsplit(path, ':')))
				exit (EXIT_FAILURE);
			free(path);
			return (result);
		}
		i++;
	}
	return (NULL);
}

char				*find_path_exe(char **path_dir, char *exe)
{
	struct stat		filestat;
	char			*path;
	size_t			i = 0;

	if (!*path_dir || !exe)
		return (NULL);
	if (exe[0] == '/')
	{
		if (!stat(exe, &filestat))
		{
			if (!(path = ft_strdup(exe)))
				exit(EXIT_FAILURE);
			return (path);
		}
		return (NULL);
	}
	while (path_dir[i])
	{
		if (!(path = ft_strjoin3(path_dir[i], "/", exe)))
			exit(EXIT_FAILURE);
		if (!stat(path, &filestat))
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

int				check_path_access(char *path)
{
	if (!path)
		return (0);
	if ((access(path, X_OK)) < 0)
		return (-1);
	else if ((access(path, X_OK)) == 0)
		return (1);
	return (0);
}

int				is_binary_exe(char **environ, char **args, char *exe)
{
	char		**path_dir;
	char		*path;
	
	if (!*environ || !*args || !exe)
		return (0);
	if (!(path_dir = get_path_dir(environ)))
		return (-1);
	path = find_path_exe(path_dir, exe);
	ft_tabfree(&path_dir);
	if (check_path_access(path) < 0)
	{
		ft_putstr(exe);
		ft_putstr(": Permission denied for execution.\n");
		return (-1);
	}
	else if (check_path_access(path) == 0)
	{
		ft_putstr(exe);
		ft_putstr(": Command not found.\n");
		return (0);
	}
	else if (check_path_access(path))
		execute_bin(path, args);
	free(path);
	ft_tabfree(&args);
	return (1);
}
