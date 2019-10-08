/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:14:07 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 20:26:09 by srobin           ###   ########.fr       */
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
				exit(EXIT_FAILURE);
			free(path);
			return (result);
		}
		i++;
	}
	return (NULL);
}

static void			print_error(char *exe, int opt)
{
	if (!exe)
		return ;
	ft_putstr_fd(exe, 2);
	if (opt == 1)
		ft_putendl_fd(": Permission denied for execution.", 2);
	else if (opt == 0)
		ft_putendl_fd(": Command not found.", 2);
	else if (opt == 2)
		ft_putendl_fd(": Is a directory.", 2);
}

int					check_path_access(char *path, int *i)
{
	struct stat		filestat;

	if (!path && (lstat(path, &filestat) == -1))
	{
		*i = 0;
		return (0);
	}
	if (lstat(path, &filestat) == 0)
	{
		if ((S_ISDIR(filestat.st_mode)))
			return ((*i = 2) && 0);
		else if ((access(path, X_OK)) < 0)
		{
			*i = 1;
			return (0);
		}
	}
	else if ((access(path, X_OK)) == 0)
	{
		*i = 0;
		return (0);
	}
	return (1);
}

char				*find_path_exe(char **path_dir, char *exe)
{
	struct stat		filestat;
	char			*path;

	if (!path_dir)
	{
		if (lstat(exe, &filestat) == -1)
			return (NULL);
		return ((path = ft_strdup(exe)));
	}
	if (exe[0] == '/' || (exe[0] == '.' && exe[1] && exe[1] == '/'))
	{
		if (!lstat(exe, &filestat))
		{
			if (!(path = ft_strdup(exe)))
				exit(EXIT_FAILURE);
			return (path);
		}
		return (NULL);
	}
	if (!(check_is_file(&path, path_dir, exe)))
		return (NULL);
	else
		return (path);
}

int					is_binary_exe(char **environ, char **args, char *exe)
{
	char			**path_dir;
	char			*path;
	int				i;

	if (!*environ || !*args || !exe)
		return (0);
	path_dir = get_path_dir(environ);
	path = find_path_exe(path_dir, exe);
	if (path_dir)
		ft_tabfree(&path_dir);
	if (check_path_access(path, &i) == 0)
		print_error(exe, i);
	else
		execute_bin(path, args, environ);
	ft_strdel(&path);
	return (1);
}
