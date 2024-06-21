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
#include "../include/px_exit.h"
#include "../include/px_types.h"

int	px_close(int *fd)
{
	if (*fd > -1)
		return (close(*fd));
	return (0);
}

void	px_close__program(int *fd, t_program *program, t_process *process)
{
	if (px_close(fd) == -1)
	{
		px_process__free(process);
		px_exit__generic(__func__, program, FREE_PROGRAM, PX_EXIT_FAILURE);
	}
	*fd = -1;
}

void	px_close__cmd(int *fd, t_cmd *cmd)
{
	if (px_close(fd) == -1)
		px_exit__generic(__func__, cmd, FREE_CMD, PX_EXIT_FAILURE);
	*fd = -1;
}

void	px_close__program_full(int fd[2],
			t_program *program, t_process *process)
{
	px_close__program(&fd[0], program, process);
	px_close__program(&fd[1], program, process);
}

void	px_close__cmd__full(int fd[2], t_cmd *cmd)
{
	px_close__cmd(&fd[0], cmd);
	px_close__cmd(&fd[1], cmd);
}
