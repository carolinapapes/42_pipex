/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:29:13 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 15:25:27 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "pipex.h"
#include "px_process.h"
#include "px_types.h"
#include "px_program.h"

void	px_process__free(void *process)
{
	if (process)
		free(process);
	process = NULL;
	return ;
}

void	px_process__fork(t_process *process)
{
	process->pid = fork();
	if (process->pid == -1)
		perror_msg("fork");
}

void	px_process__wait(t_process *process)
{
	waitpid(process->pid, NULL, 0);
}

void	px_process__exit(char *msg, t_program *program, t_process *process)
{
	perror_msg(msg);
	if (process)
		px_process__free(process);
	if (program)
		px_program__free(program);
	exit(1);
}
