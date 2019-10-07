/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:20:34 by srobin            #+#    #+#             */
/*   Updated: 2019/10/07 17:34:34 by srobin           ###   ########.fr       */
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
char		**env_cpy(char **environ);
int			execute_bin(char *path, char **args);
int			execute_builtin(char ***environ, char **args);
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
**			setenv.c
*/
int			ft_setenv(char ***environ, char **args);
void		swap_env(char **environ, char *arg, char *arg2);
/*
**			unsetenv.c	
*/
int			ft_unsetenv(char ***environ, char **args);
/*
**			pwd.c
*/
int			ft_pwd(char **environ, char **args);
/*
**			exit.c
*/
int			ft_exit(char *arg);

#endif
