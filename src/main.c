/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:37:46 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/11 22:55:24 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libs/libft/libft.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	if (!is_parse_valid(argc, argv))
		return (1);
	return (pipex_new(argc, argv, env));
}