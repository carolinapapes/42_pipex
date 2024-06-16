/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:29:13 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 08:57:03 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "pipex.h"
#include "px_process.h"
#include "px_types.h"

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
