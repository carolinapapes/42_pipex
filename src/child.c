/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:27:50 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/11 22:55:52 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"
#include "files_fd.h"
#include <stdlib.h>
#include <stdio.h>

void	fd_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	process_child(int *fd_read, int *fd_output, char *command, char **env)
{
	int	i;

	process_fds(fd_read, fd_output, FT_FD_INIT | FT_FD_ERROR | FT_FD_DUP);
	i = command_call(command, env);
	process_fds(fd_read, fd_output, FT_FD_CLOSE);
	exit(i);
}