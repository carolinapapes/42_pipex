/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process__wait.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:13:16 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 06:07:27 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include "../include/px_types.h"
#include "../include/px_exit.h"

static void	wait__check(t_process *process)
{
	if (process && process->pid != -1)
		waitpid(process->pid, NULL, 0);
}

static void	wait__all(t_program *program, t_process *process, int *status)
{
	ft_lstiter(program->list, (void *)wait__check);
	waitpid(process->pid, status, 0);
}

void	px_process__wait(t_program *program)
{
	int			status;
	t_process	*process;

	process = content(program);
	program->list->content = NULL;
	wait__all(program, process, &status);
	px_free(program, process);
	status = WEXITSTATUS(status);
	exit (status);
}
