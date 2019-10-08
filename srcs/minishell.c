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

	environ_cpy = env_cpy(environ);
	while (19)
		get_input(&input, &environ_cpy);
	return (argc && argv && 0);
}
