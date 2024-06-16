/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:15:21 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 09:22:01 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"
#include "px_program.h"

void	px_program__free(t_program *program)
{
	if (program->cmdv)
		free(program->cmdv);
	program->cmdv = NULL;
	return ;
}

static void	px_cmds_allocate(t_program *program, int cmdc)
{
	program->cmdv = (char **)malloc(sizeof(char *) * (cmdc + 1));
	if (program->cmdv)
	{
		return ;
	}
	perror_msg("Pipex: Fatal: failed to allocate memory.\n");
	exit(1);
}

static void	px_cmds_assing(t_program *program, char **argv, int argc)
{
	int	i;

	i = 1;
	while (++i < argc - 1)
		program->cmdv[i - 2] = argv[i];
	program->cmdv[i - 2] = NULL;
	return ;
}

static void	px_program_assing(t_program *program, char **argv, int argc, char **env)
{
	program->fd_names[READ_END] = argv[1];
	program->fd_names[WRITE_END] = argv[argc - 1];
	program->env = env;
	return ;
}



/**
	* BRIEF:  
	* Program will handle all the validated inputs from main and 
	* will assign them to the pipex program struct.
	*
	* DESCRIPTION: 
	* The first and last variables are the file names that will be used as i/o.
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
	px_program_assing(program, argv, argc, env);
	px_cmds_allocate(program, argc - 3);
	px_cmds_assing(program, argv, argc);
	return ;
}
