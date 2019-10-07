/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:20:24 by srobin            #+#    #+#             */
/*   Updated: 2019/10/07 18:30:45 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(void)
{
	extern char	**environ;
	char		**environ_cpy;
	char		*input;
	char		**args;

	environ_cpy = env_cpy(environ);
	while (19)
	{
		ft_putstr("$> ");
		get_next_line(0, &input);
		args = ft_split_whitespaces(input);
		if (!ft_strcmp(args[0], "unsetenv"))
			ft_unsetenv(&environ_cpy, args);
		if (!(ft_exit(args[0])))
			break ;
		else if (!execute_builtin(&environ_cpy, args))
			is_binary_exe(environ_cpy, args, args[0]);
		free(input);
	}
	return (0);
}
