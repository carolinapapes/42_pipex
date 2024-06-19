/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd__fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:21:52 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/19 22:18:29 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../include/px_fd.h"
#include "../include/px_types.h"
#include "../include/px_exit.h"

static void	fd_init(int *input, int *output, t_process *process)
{
	px_close__check(&input[WRITE_END], NULL, process);
	px_close__check(&output[READ_END], NULL, process);
}

static void	fd_close(int *input, int *output, t_process *process)
{
	px_close__check(&input[READ_END], NULL, process);
	px_close__check(&output[WRITE_END], NULL, process);
}

static void	fd_dup(int *input, int *output, t_process *process)
{
	if (input[READ_END] > -1 && dup2(input[READ_END], STDIN_FILENO) == -1)
		px_exit("dup2", NULL, process);
	if (output[WRITE_END] > -1 && dup2(output[WRITE_END], STDOUT_FILENO) == -1)
		px_exit("dup2", NULL, process);
}

static void	fd_error(int *input, int *output)
{
	if (input[READ_END] == -1 || output[WRITE_END] == -1)
		exit(1);
}

void	px_cmd__fd(t_process *process, int code)
{
	int	*input;
	int	*output;

	input = process->input;
	output = process->output;
	if (code & FT_FD_INIT)
		fd_init(input, output, process);
	if (code & FT_FD_ERROR)
		fd_error(input, output);
	if (code & FT_FD_DUP)
		fd_dup(input, output, process);
	if (code & FT_FD_CLOSE)
		fd_close(input, output, process);
}
