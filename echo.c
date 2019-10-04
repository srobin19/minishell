/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 20:24:33 by srobin            #+#    #+#             */
/*   Updated: 2019/10/05 01:44:15 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_echo(char **args)
{
	size_t	i;

	if (!args)
		return (0);
	i = 1;
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			ft_putchar(' ');
		else
			ft_putchar('\n');
		i++;
	}
	return (1);
}
