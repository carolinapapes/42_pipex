/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:15:21 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 00:19:01 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../include/px_exit.h"
#include "../include/px_types.h"

static void	cmds_allocate(t_program *program, int cmdc)
{
	program->cmdv = (char **)malloc(sizeof(char *) * cmdc);
	if (program->cmdv)
		return ;
	px_exit("malloc error", program, NULL);
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
}

/**
	* @brief: Program will handle all the validated inputs from main and 
	* will assign them to the pipex program struct.
	*
	* @description: The first&&last variables are the file names.
	* They will assigened to the program struct as fd_names. 
	* The argv and argc arguments will be changed to the parameters needed.
	* The enviroment will be the same as the one that the program is running.
	*
	* ALLOCATED: program.cmdv.
	* ERROR: malloc error.
	* EXIT: 1 on malloc error.
*/

void	px_program(t_program *program, int argc, char **argv, char **env)
{
	initialize(program, argv, argc, env);
	cmds_allocate(program, argc - 2);
	cmds_assing(program, argv, argc);
}
