/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:22:11 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/06 23:10:17 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libs/libft/libft.h"

int	is_argc_err(int argc)
{
	return (argc > 10);
}

int	is_str_null(char *str)
{
	return (!str);
}

int	find_args(int argc, char **argv, int (*f)(char *str))
{
	int	i;

	i = -1;
	while (++i < argc)
		if (f(argv[i]))
			return (1);
	return (0);
}

int	is_parse_valid(int argc, char **argv)
{
	if (is_argc_err(argc) \
		|| find_args(argc, argv, is_str_null))
		return (ft_putstr_fd("Pipex: invalid args.\n", 1), 0);
	return (1);
}
