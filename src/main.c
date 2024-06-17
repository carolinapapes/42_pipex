/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:37:46 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 17:09:26 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"
#include "px_fd.h"
#include "px_program.h"
#include "px_types.h"

int	main(int argc, char **argv, char **env)
{
	t_program	program;

	px_validate_input(argc, argv);
	px_program(&program, argc, argv, env);
	px_process(&program);
	px_program__free(&program);
	return (0);
}
