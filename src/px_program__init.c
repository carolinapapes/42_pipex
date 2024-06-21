/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_program__init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:15:21 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/19 22:12:56 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/px_exit.h"
#include "../include/px_types.h"

static void	cmds_allocate(t_program *program, int cmdc)
{
	program->cmdv = (char **)malloc(sizeof(char *) * cmdc);
	if (program->cmdv)
		return ;
	px_exit__generic(__func__, NULL, 0, PX_EXIT_FAILURE);
}

static void	cmds_assing(t_program *program, char **argv, int argc)
{
	int	i;

	i = 1;
	while (++i < argc - 1)
		program->cmdv[i - 2] = argv[i];
	program->cmdv[i - 2] = NULL;
}

static void	initialize(t_program *program, char **argv, int argc, char **env)
{
	program->fd_names[READ_END] = argv[1];
	program->fd_names[WRITE_END] = argv[argc - 1];
	program->env = env;
	program->list = NULL;
	program->cmdv = NULL;
}

/**
	* @brief handles all the validated inputs and add them to program struct.
	* @note Allocates memory for cmdv (the first pointer). Exits if fails.
*/
void	px_program__init(t_program *program, int argc, char **argv, char **env)
{
	initialize(program, argv, argc, env);
	cmds_allocate(program, argc - 2);
	cmds_assing(program, argv, argc);
}
