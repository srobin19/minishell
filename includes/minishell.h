/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:20:34 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 21:13:59 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>

/*
** 			util.c
*/
char		**env_cpy(char **environ);
int			execute_bin(char *path, char **args, char **env_cpy);
int			execute_builtin(char ***environ, char **args);
void		find_env(char **my_env, char **env_variable, char *name);
void		sub_my_env(char **sub, char *line);
/*
** 			path.c
*/
char		**get_path_dir(char **environ);
char		*find_path_exe(char **path_dir, char *exe);
int			check_path_access(char *path, int *i);
int			is_binary_exe(char **environ, char **args, char *exe);
/*
**			parse.c
*/
char		**get_input(char **input, char ***environ_cpy);
int			check_is_file(char **path, char **path_dir, char *exe);
/*
**			echo.c
*/
int			ft_echo(char **args);
/*
** 			cd.c
*/
int			set_oldpwd_env(char ***environ, char *oldpath, int opt);
int			set_pwd_env(char ***environ);
int			ft_cd(char **environ, char **args);
/*
**			cd2.c
*/
void		cd_msg(char *path);
int			check_cd(char **args);
int			cd_back(char ***environ, char **args, char *oldpath);
/*
**			env.c
*/
int			ft_env(char **environ);
void		swap_env(char **environ, char *arg, char *arg2);
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
/*
**dollars_expansion
*/
void		transform_expansions_dollars(char **transform, char *line_clean,
			char **my_env);
void		concat_dollars(char **my_env, char **transform, char *sub,
			char *line);
/*
**tildes_expansion
*/
void		transform_expansions_tildes(char **transform, char *line_clean,
			char **my_env);
void		rest_tilde(char *line, char **transform);
void		free_rest_tilde(char **s1, char **s2);
void		initialize_rest_tilde(char **tmp, int *i, int j);
/*
**check_expansion
*/
void		check_expansions(char ***result, char **environ_cpy);
void		transform_if_expansions(char **copy_line_clean, char *line_clean,
			char **my_env);
void		transform_expansions(char *line_clean, char **my_env,
			char **transform);
void		concatenation_beginnig_and_expansion(char **transform, int start,
			char *line_clean);
void		initialize_tranform_if_expansions(int *i, int *expansion,
			char **transform);
#endif
