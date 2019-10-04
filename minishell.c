/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:20:24 by srobin            #+#    #+#             */
/*   Updated: 2019/10/04 20:32:29 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(void)
{
	extern char	**environ;
	char		*input;
	char		**args;

	while (1)
	{
		ft_putstr("$> ");
		get_next_line(0, &input);
		args = ft_split_whitespaces(input);
		ft_echo(args);
		return (1);
//		is_binary_exe(environ, args, args[0]);

	}
	return (0);
}
