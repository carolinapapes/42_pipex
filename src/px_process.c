/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:26:02 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 11:05:22 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/pipex.h"
#include "../include/px_fd.h"
#include "../include/px_types.h"
#include "../include/px_process.h"
#include <stdio.h>

/**
 * BRIEF: Executes the commands in the program
 * 
 * Each iteration will:
 * create a process
 * open FDs (pipes or files)
 * fork the process
 * in child process:
 * 	 execute the comand
 * in parente process:
 * 	 close the pipes
 * 	 wait for the child process to finish
 *	 free the process
 * 
 * @param program: The program to be executed
 * @return int: 0 if the program was executed successfully
 * 
 * ALLOCATED: program->cmdv, list, list->content(process);
 */

void	px_process(t_program *program)
{
	char		**cmdv;


	cmdv = program->cmdv;
	while (cmdv[0])
	{
		px_process__init(program);
		px_process__fd_open(program, !cmdv[1]);
		px_process__fork(content(program->list), program);
		if (!(content(program->list)->pid))
			px_process__exec(program, cmdv[0]);
		px_process__fd_close(program->list, program);
		cmdv++;
	}
	px_process__wait(program);
}
