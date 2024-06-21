/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:37:46 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 22:54:25 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/px_parser.h"
#include "../include/px_program.h"
#include "../include/px_types.h"

int	main(int argc, char **argv, char **env)
{
	t_program	program;

	px_validate_input(argc, argv);
	px_program__init(&program, argc, argv, env);
	px_program__exec(&program);
	px_program__free(&program);
	return (0);
}
