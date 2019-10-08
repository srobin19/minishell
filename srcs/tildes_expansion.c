/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tildes_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:08:57 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 20:08:58 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		initialize_rest_tilde(char **tmp, int *i, int j)
{
	*tmp = NULL;
	*i = j;
}

void		free_rest_tilde(char **s1, char **s2)
{
	if (*s1)
		ft_strdel(s1);
	if (*s2)
		ft_strdel(s2);
}

void		rest_tilde(char *line, char **transform)
{
	int		i;
	char	*tmp;
	char	*sub;

	initialize_rest_tilde(&tmp, &i, -1);
	while (line[++i])
	{
		if (line[i] == '$')
		{
			if (!(sub = ft_strsub(line, 0, i)))
				exit(EXIT_FAILURE);
			tmp = *transform;
			if (!(*transform = ft_strjoin(*transform ? *transform : "", sub)))
				exit(EXIT_FAILURE);
			free_rest_tilde(&tmp, &sub);
			break ;
		}
	}
	if (!line[i])
	{
		tmp = *transform;
		if (!(*transform = ft_strjoin(*transform ? *transform : "", line)))
			exit(EXIT_FAILURE);
		ft_strdel(&tmp);
	}
}

void		transform_expansions_tildes(char **transform, char *line_clean,
		char **my_env)
{
	int		i;
	char	*tmp;
	char	*env_variable;

	i = 0;
	tmp = NULL;
	env_variable = NULL;
	if (line_clean[i + 1] == '\0' || line_clean[i + 1] == '/')
	{
		find_env(my_env, &env_variable, "HOME");
		if (!env_variable)
			env_variable = "~";
		tmp = *transform;
		if (!(*transform = ft_strjoin(*transform ? *transform : "",
						env_variable)))
			exit(EXIT_FAILURE);
		ft_strdel(&tmp);
		tmp = *transform;
		if (!(*transform = ft_strjoin(*transform, &line_clean[i + 1])))
			exit(EXIT_FAILURE);
		ft_strdel(&tmp);
	}
	else
		rest_tilde(&line_clean[i], transform);
}
