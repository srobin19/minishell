/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 20:24:33 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 21:45:24 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			nflag(char **cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd[i])
	{
		j = 1;
		if (cmd[i][0] != '-')
			return (i);
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int			ft_echo(char **final_result)
{
	int i;
	int iteration;
	int flag;

	iteration = 0;
	final_result++;
	i = nflag(final_result);
	flag = (i > 0) ? 1 : 0;
	while (final_result[i])
	{
		if (iteration > 0)
			ft_putstr(" ");
		ft_putstr(final_result[i]);
		i++;
		iteration++;
	}
	if (!flag)
		ft_putendl("");
	return (1);
}
