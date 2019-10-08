/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 22:26:25 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 21:14:12 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		swap_env(char **environ, char *arg, char *arg2)
{
	if (!environ || !arg)
		return ;
	free(*environ);
	if (!(*environ = ft_strjoin3(arg, "=", arg2)))
		exit(EXIT_FAILURE);
}

int			ft_env(char **environ)
{
	if (!environ)
		return (0);
	ft_print_tab(environ);
	return (1);
}
