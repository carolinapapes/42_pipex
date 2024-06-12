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
#include "files_fd.h"
#include <stdlib.h>
#include <stdio.h>

void	process_fds_init(int *fd_input, int *fd_output)
{
	close(fd_input[WRITE_END]);
	close(fd_output[READ_END]);
}

void	process_fds_close(int *fd_input, int *fd_output)
{
	close(fd_input[READ_END]);
	close(fd_output[WRITE_END]);
}

void	process_fds_dup(int *fd_input, int *fd_output)
{
	dup2(fd_input[READ_END], STDIN_FILENO);
	dup2(fd_output[WRITE_END], STDOUT_FILENO);
}

void	process_fds_error(int *fd_input, int *fd_output)
{
	if (fd_input[READ_END] == -1 || fd_output[WRITE_END] == -1)
		exit(1);
}

// Check exits in the code - if this exits as 1, what should happen in main?
void	process_fds(int *fd_input, int *fd_output, int code)
{
	if (code & FT_FD_INIT)
		process_fds_init(fd_input, fd_output);
	if (code & FT_FD_ERROR)
		process_fds_error(fd_input, fd_output);
	if (code & FT_FD_DUP)
		process_fds_dup(fd_input, fd_output);
	if (code & FT_FD_CLOSE)
		process_fds_close(fd_input, fd_output);
}
