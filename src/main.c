/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:37:46 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 21:51:02 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libs/libft/libft.h"
#include <stdio.h>
#include "px_program.h"

int	main(int argc, char **argv, char **env)
{
	t_program	program;

	px_validate_input(argc, argv);
	px_program(&program, argc, argv, env);
	pipex_new(&program);
	px_program__free(&program);

	return (0);
}
