/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd__fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:21:52 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 00:06:43 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/px_fd.h"
#include "../include/px_types.h"
#include "../include/px_exit.h"

static void	fd_init(int *input, int *output)
{
	px_close__check(&input[WRITE_END], NULL, NULL);
	px_close__check(&output[READ_END], NULL, NULL);
}

static void	fd_close(int *input, int *output)
{
	px_close__check(&input[READ_END], NULL, NULL);
	px_close__check(&output[WRITE_END], NULL, NULL);
}

static void	fd_dup(int *input, int *output)
{
	if (input[READ_END] > -1 && dup2(input[READ_END], STDIN_FILENO) == -1)
		px_exit("dup2", NULL, NULL);
	if (output[WRITE_END] > -1 && dup2(output[WRITE_END], STDOUT_FILENO) == -1)
		px_exit("dup2", NULL, NULL);
}

static void	fd_error(int *input, int *output)
{
	if (input[READ_END] == -1 || output[WRITE_END] == -1)
		exit(1);
}

void	px_cmd__fd(t_cmd *cmd, int code)
{
	int	*input;
	int	*output;

	input = cmd->input;
	output = cmd->output;
	if (code & FT_FD_INIT)
		fd_init(input, output);
	if (code & FT_FD_ERROR)
		fd_error(input, output);
	if (code & FT_FD_DUP)
		fd_dup(input, output);
	if (code & FT_FD_CLOSE)
		fd_close(input, output);
}
