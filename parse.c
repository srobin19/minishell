/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 20:33:59 by srobin            #+#    #+#             */
/*   Updated: 2019/10/07 21:02:23 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**get_input(char **input)
{
	char		**result;

	ft_putstr("$> ");
	get_next_line(0, input);
	if (!(result = ft_split_whitespaces(*input)))
		exit(EXIT_FAILURE);
	return (result);
}
