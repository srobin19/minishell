/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:20:34 by srobin            #+#    #+#             */
/*   Updated: 2019/10/05 01:44:44 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>

# define HOME "/Users/srobin"

/*
** 			util.c
*/
int			execute_bin(char *path, char **args);
int			execute_builtin(char **environ, char **args);
/*
** 			path.c 
*/
char		**get_path_dir(char **environ);
char		*find_path_exe(char **path_dir, char *exe);
int			check_path_access(char *path);
int			is_binary_exe(char **environ, char **args, char *exe);
/*
**			echo.c
*/
int			ft_echo(char **args);
/*
** 			cd.c
*/
int			ft_cd(char **environ, char **args);
/*
**			env.c
*/
int			ft_env(char **environ);
/*
**			pwd.c
*/
int			ft_pwd(char **environ, char **args);
/*
**			exit.c
*/
int			ft_exit(char *arg);

#endif
