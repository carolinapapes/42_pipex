/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:37:59 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 23:56:45 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "px_fd.h"
#include <stdlib.h>
#include <stdio.h>

void	px_pipes_fd_init(int *fd_input, int *fd_output)
{
	if (fd_input[WRITE_END] != -1) 
		close(fd_input[WRITE_END]);
	if (fd_output[READ_END] != -1) 
		close(fd_output[READ_END]);
}

void	px_pipes_fd_close(int *fd_input, int *fd_output)
{
	if (fd_input[READ_END] != -1)
		close(fd_input[READ_END]);
	if (fd_output[WRITE_END] != -1)
		close(fd_output[WRITE_END]);
}

void	px_pipes_fd_dup(int *fd_input, int *fd_output)
{
	dup2(fd_input[READ_END], STDIN_FILENO);
	dup2(fd_output[WRITE_END], STDOUT_FILENO);
}

// clean this exit
void	px_pipes_fd_error(int *fd_input, int *fd_output)
{
	if (fd_input[READ_END] == -1 || fd_output[WRITE_END] == -1)
		exit(1);
}

// Check exits in the code - if this exits as 1, what should happen in main?
void	px_pipes_fd(int *fd_input, int *fd_output, int code)
{
	if (code & FT_FD_INIT)
		px_pipes_fd_init(fd_input, fd_output);
	if (code & FT_FD_ERROR)
		px_pipes_fd_error(fd_input, fd_output);
	if (code & FT_FD_DUP)
		px_pipes_fd_dup(fd_input, fd_output);
	if (code & FT_FD_CLOSE)
		px_pipes_fd_close(fd_input, fd_output);
}

void	fd_close(int *fd)
{
	if (fd[READ_END] != -1)
		close(fd[READ_END]);
	if (fd[WRITE_END] != -1)
		close(fd[WRITE_END]);
}
