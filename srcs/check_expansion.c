/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:05:32 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 20:18:24 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		initialize_tranform_if_expansions(int *i, int *expansion,
	char **transform)
{
	*i = -1;
	*transform = NULL;
	*expansion = 0;
}

void		concatenation_beginnig_and_expansion(char **transform, int start,
		char *line_clean)
{
	char	*sub;
	char	*tmp;

	sub = NULL;
	tmp = NULL;
	if (!(sub = ft_strsub(line_clean, 0, start)))
		exit(EXIT_FAILURE);
	tmp = *transform;
	if (!(*transform = ft_strjoin(sub, *transform ? *transform : "")))
		exit(EXIT_FAILURE);
	ft_strdel(&tmp);
	ft_strdel(&sub);
}

void		transform_expansions(char *line_clean, char **my_env,
		char **transform)
{
	int i;
	int dollar;
	int start;

	i = -1;
	dollar = -1;
	while (line_clean[++i])
	{
		if (line_clean[i] == '$')
		{
			start = i;
			dollar = 1;
			transform_expansions_dollars(transform, &line_clean[i], my_env);
			break ;
		}
		else if (line_clean[i] == '~' && dollar == -1 && i == 0)
		{
			start = i;
			transform_expansions_tildes(transform, &line_clean[i], my_env);
		}
	}
	concatenation_beginnig_and_expansion(transform, start, line_clean);
}

void		transform_if_expansions(char **copy_line_clean, char *line_clean,
		char **my_env)
{
	int		i;
	int		expansion;
	char	*transform;

	initialize_tranform_if_expansions(&i, &expansion, &transform);
	while (line_clean[++i])
	{
		if (line_clean[i] == '$' || line_clean[i] == '~')
		{
			expansion = 1;
			break ;
		}
	}
	if (expansion == 1)
	{
		transform_expansions(line_clean, my_env, &transform);
		if (!(*copy_line_clean = ft_strdup(transform)))
			exit(EXIT_FAILURE);
		ft_strdel(&transform);
	}
	else
	{
		if (!(*copy_line_clean = ft_strdup(line_clean)))
			exit(EXIT_FAILURE);
	}
}

void		check_expansions(char ***result, char **environ_cpy)
{
	int		i;
	char	**final_result;
	char	*copy_line_clean;

	i = -1;
	copy_line_clean = NULL;
	if (!(final_result = (char**)malloc(sizeof(char*)
					* ft_tablen(*result) + 1)))
		exit(EXIT_FAILURE);
	while ((*result)[++i])
	{
		transform_if_expansions(&copy_line_clean, (*result)[i], environ_cpy);
		if (!(final_result[i] = ft_strdup(copy_line_clean)))
			exit(EXIT_FAILURE);
		ft_strdel(&copy_line_clean);
	}
	final_result[i] = 0;
	ft_tabfree(result);
	*result = final_result;
}
