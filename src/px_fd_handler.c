/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fd_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:21:52 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 22:38:55 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../include/px_fd.h"
#include "../include/px_types.h"
#include "../include/px_exit.h"

static void	px_fd__init(int *fd_input, int *fd_output, t_process *process)
{
	px_close__check(fd_input[WRITE_END], NULL, process);
	px_close__check(fd_output[READ_END], NULL, process);
}

static void	px_fd__close(int *fd_input, int *fd_output, t_process *process)
{
	px_close__check(fd_input[READ_END], NULL, process);
	px_close__check(fd_output[WRITE_END], NULL, process);
}

static void	px_fd__dup(int *fd_input, int *fd_output, t_process *process)
{
	if (fd_input[READ_END] > -1 && dup2(fd_input[READ_END], STDIN_FILENO) == -1)
		px_exit("dup2", NULL, process);
	if (fd_output[WRITE_END] > -1 && dup2(fd_output[WRITE_END], STDOUT_FILENO) == -1)
		px_exit("dup2", NULL, process);
}

static void	px_fd__error(int *fd_input, int *fd_output)
{
	if (fd_input[READ_END] == -1 || fd_output[WRITE_END] == -1)
		exit(1);
}

void	px_fd__handler(t_process *process, int code)
{
	int *fd_input;
	int *fd_output;

	fd_input = process->input;
	fd_output = process->output;
	if (code & FT_FD_INIT)
		px_fd__init(fd_input, fd_output, process);
	if (code & FT_FD_ERROR)
		px_fd__error(fd_input, fd_output);
	if (code & FT_FD_DUP)
		px_fd__dup(fd_input, fd_output, process);
	if (code & FT_FD_CLOSE)
		px_fd__close(fd_input, fd_output, process);
}
