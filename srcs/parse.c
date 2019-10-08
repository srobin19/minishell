/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 20:33:59 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 22:01:14 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_is_file(char **path, char **path_dir, char *exe)
{
	struct stat		filestat;

	while (*path_dir)
	{
		if (!(*path = ft_strjoin3(*path_dir, "/", exe)))
			exit(EXIT_FAILURE);
		if (!lstat(*path, &filestat))
			return (1);
		ft_strdel(path);
		path_dir++;
	}
	return (0);
}

static char		**split_args(char **args, char *input_str, size_t ac)
{
	char	*roam;
	char	*start;
	int		arg_len;
	size_t	i;

	i = 0;
	while (input_str[i] && (input_str[i] == '\t' || input_str[i] == ' '))
		i++;
	if (!input_str[i])
		return (NULL);
	i = -1;
	roam = input_str;
	while (*roam && ++i < ac)
	{
		while (*roam && ft_isspacer(*roam))
			roam++;
		arg_len = 0;
		start = roam;
		while (*roam && !ft_isspacer(*roam++))
			arg_len++;
		if (!(args[i] = strndup(start, arg_len)))
			exit(EXIT_FAILURE);
	}
	args[(int)ac] = NULL;
	return (args);
}

static void		utils_get_input(char **input, char ***split_exe)
{
	ft_putstr("\033[33m\033[01m$> \033[0m");
	if (get_next_line(0, input) < 0)
		exit(EXIT_FAILURE);
	if (!(*split_exe = ft_strsplit(*input, ';')))
		exit(EXIT_FAILURE);
	ft_strdel(input);
}

char			**get_input(char **input, char ***environ_cpy)
{
	char		**result;
	int			words;
	int			i;
	char		**split_exe;

	i = -1;
	split_exe = NULL;
	utils_get_input(input, &split_exe);
	while (split_exe[++i])
	{
		words = ft_nb_words(split_exe[i]);
		if (!(result = (char**)malloc(sizeof(char*) * (words + 1))))
			exit(EXIT_FAILURE);
		result = split_args(result, split_exe[i], words);
		if (!result)
			return (NULL);
		check_expansions(&result, *environ_cpy);
		if (!(ft_exit(result[0])))
			exit(EXIT_SUCCESS);
		else if (!execute_builtin(environ_cpy, result))
			is_binary_exe(*environ_cpy, result, result[0]);
		ft_tabfree(&result);
	}
	ft_tabfree(&split_exe);
	return (NULL);
}
