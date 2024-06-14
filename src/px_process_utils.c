/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:29:13 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 22:57:38 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_types.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "pipex.h"
#include "px_process.h"

void	px_process__free(void *process)
{
	if (process)
		free(process);
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

// before exit this function must free program cmds or return
// clean list and program and exit
void	px_process__allocate(t_process **process)
{
	*process = (t_process *)malloc(sizeof(t_process));
	if (*process)
		return ;
	perror_msg("process allocation failed");
	return ;
}

void	px_process__init(t_process *process)
{
	process->pid = -1;
	process->input[0] = -1;
	process->input[1] = -1;
	process->output[0] = -1;
	process->output[1] = -1;
	return ;
}
