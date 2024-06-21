/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:37:59 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 00:05:58 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/px_types.h"
#include "../include/pipex.h"
#include "../include/px_exit.h"
#include <stdio.h>

void	px_close__check(int *fd, t_program *program, t_process *process)
{
	if (*fd < 0)
		return ;
	if (close(*fd) == -1)
	{
		px_process__free(process);
		px_exit("close", program);
	}
	*fd = -1;
}

void	px_close__full(int fd[2], t_program *program, t_process *process)
{
	px_close__check(&fd[0], program, process);
	px_close__check(&fd[1], program, process);
}
