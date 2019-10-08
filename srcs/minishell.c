/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:20:24 by srobin            #+#    #+#             */
/*   Updated: 2019/10/08 20:17:53 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(int argc, char **argv, char **environ)
{
	char		**environ_cpy;
	char		*input;
	char		**args;

	environ_cpy = env_cpy(environ);
	while (19)
	{
		if (!(args = get_input(&input, environ_cpy)))
			continue ;
		if (!(ft_exit(args[0])))
			exit(EXIT_SUCCESS);
		else if (!execute_builtin(&environ_cpy, args))
			is_binary_exe(environ_cpy, args, args[0]);
		ft_tabfree(&args);
		ft_strdel(&input);
	}
	return (argc && argv && 0);
}
