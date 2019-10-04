/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:20:34 by srobin            #+#    #+#             */
/*   Updated: 2019/10/04 20:29:11 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>

/*
** util.c
*/
int			execute(char *path, char **args, char *exe);

/*
** path.c 
*/
char		**get_path_dir(char **environ);
char		*find_path_exe(char **path_dir, char *exe);
int			check_path_access(char *path);
int			is_binary_exe(char **environ, char **args, char *exe);

/*
** echo.c
*/
void		ft_echo(char **args);

#endif
