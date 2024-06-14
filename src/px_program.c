/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:15:21 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 22:15:38 by carolinapap      ###   ########.fr       */
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
	return ;
}

void	px_cmds_allocate(t_program *program)
{
	program->cmdv = (char **)malloc(sizeof(char *) * (program->cmdc + 1));
	if (program->cmdv)
	{
		return ;
	}
	perror_msg("Pipex: malloc error.\n");
	exit(1);
}

void	px_cmds_assing(t_program *program, char **argv, int argc)
{
	int	i;

	i = 1;
	while (++i < argc - 1)
		program->cmdv[i - 2] = argv[i];
	program->cmdv[i - 2] = NULL;
	return ;
}

void	px_program_assing(t_program *program, char **argv, int argc, char **env)
{
	program->fd_names[READ_END] = argv[1];
	program->fd_names[WRITE_END] = argv[argc - 1];
	program->cmdc = argc - 3;
	program->env = env;
	return ;
}

void	px_program(t_program *program, int argc, char **argv, char **env)
{
	px_program_assing(program, argv, argc, env);
	px_cmds_allocate(program);
	px_cmds_assing(program, argv, argc);
	return ;
}
