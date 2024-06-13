/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:22:11 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 23:30:46 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libs/libft/libft.h"

int	is_argc_valid(int argc)
{
	return (argc == 5);
}

int	is_str_null(char *str)
{
	return (!str);
}

int	iterargs(int argc, char **argv, int (*f)(char *str))
{
	int	i;

	i = -1;
	while (++i < argc)
		if (f(argv[i]))
			return (0);
	return (1);
}

void	px_validate_input(int argc, char **argv)
{
	if (is_argc_valid(argc) \
		&& iterargs(argc, argv, is_str_null))
		return ;
	ft_putstr_fd("Pipex: invalid args.\n", 2);
	exit (1);
}
