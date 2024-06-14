/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:21:52 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 23:26:03 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_fd.h"
#include "px_types.h"
#include <unistd.h>
#include <stdlib.h>

void	px_pipes_fd__init(int *fd_input, int *fd_output)
{
	px_close__check(fd_input[WRITE_END]);
	px_close__check(fd_output[READ_END]);
}

void	px_pipes_fd__close(int *fd_input, int *fd_output)
{
	px_close__check(fd_input[READ_END]);
	px_close__check(fd_output[WRITE_END]);
}

// check dup2
void	px_pipes_fd__dup(int *fd_input, int *fd_output)
{
	dup2(fd_input[READ_END], STDIN_FILENO);
	dup2(fd_output[WRITE_END], STDOUT_FILENO);
}

// clean this exit
void	px_pipes_fd__error(int *fd_input, int *fd_output)
{
	if (fd_input[READ_END] == -1 || fd_output[WRITE_END] == -1)
		exit(1);
}

// Check exits in the code - if this exits as 1, what should happen in main?
void	px_pipes_fd(int *fd_input, int *fd_output, int code)
{
	if (code & FT_FD_INIT)
		px_pipes_fd__init(fd_input, fd_output);
	if (code & FT_FD_ERROR)
		px_pipes_fd__error(fd_input, fd_output);
	if (code & FT_FD_DUP)
		px_pipes_fd__dup(fd_input, fd_output);
	if (code & FT_FD_CLOSE)
		px_pipes_fd__close(fd_input, fd_output);
}
