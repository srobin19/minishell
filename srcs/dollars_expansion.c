/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_tilde_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:05:51 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 20:15:07 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		concat_dollars(char **my_env, char **transform, char *sub,
		char *line)
{
	char	*tmp;
	char	*env_variable;

	tmp = NULL;
	env_variable = NULL;
	find_env(my_env, &env_variable, sub);
	if (!env_variable)
		env_variable = "";
	tmp = *transform;
	if (!(*transform = ft_strjoin(*transform ? *transform : "", env_variable)))
		exit(EXIT_FAILURE);
	ft_strdel(&tmp);
	tmp = *transform;
	if (!(*transform = ft_strjoin(*transform ? *transform : "", line)))
		exit(EXIT_FAILURE);
	ft_strdel(&tmp);
}

void		transform_expansions_dollars(char **transform, char *line_clean,
		char **my_env)
{
	int		i;
	int		j;
	char	**array;
	char	*sub;

	if (!(array = ft_strsplit(line_clean, '$')))
		exit(EXIT_FAILURE);
	initialize_rest_tilde(&sub, &i, 0);
	while (array[i])
	{
		j = 0;
		if (ft_isdigit(array[i][j]))
			j++;
		else
		{
			while (array[i][j] && ft_isalnum(array[i][j]))
				j++;
		}
		if (!(sub = ft_strsub(array[i], 0, j)))
			exit(EXIT_FAILURE);
		concat_dollars(my_env, transform, sub, &array[i][j]);
		ft_strdel(&sub);
		i++;
	}
	ft_tabfree(&array);
}
