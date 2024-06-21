/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd__fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:21:52 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 23:45:17 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/px_fd.h"
#include "../include/px_types.h"
#include "../include/px_exit.h"

static void	fd_init(int *input, int *output, t_cmd *cmd)
{
	px_close__cmd(&input[WRITE_END], cmd);
	px_close__cmd(&output[READ_END], cmd);
}

static void	fd_close(int *input, int *output, t_cmd *cmd)
{
	px_close__cmd(&input[READ_END], cmd);
	px_close__cmd(&output[WRITE_END], cmd);
}

static void	fd_dup(int *input, int *output, t_cmd *cmd)
{
	if (input[READ_END] > -1 && dup2(input[READ_END], STDIN_FILENO) == -1)
		px_exit__generic(__func__, cmd, FREE_CMD, PX_EXIT_FAILURE);
	if (output[WRITE_END] > -1 && dup2(output[WRITE_END], STDOUT_FILENO) == -1)
		px_exit__generic(__func__, cmd, FREE_CMD, PX_EXIT_FAILURE);
}

static void	fd_error(int *input, int *output, t_cmd *cmd)
{
	if (input[READ_END] == -1 || output[WRITE_END] == -1)
		px_exit__generic(__func__, cmd, FREE_CMD, PX_EXIT_SUCESS);
}

void	px_cmd__fd(t_cmd *cmd, int code)
{
	int	*input;
	int	*output;

	input = cmd->input;
	output = cmd->output;
	if (code & FT_FD_INIT)
		fd_init(input, output, cmd);
	if (code & FT_FD_ERROR)
		fd_error(input, output, cmd);
	if (code & FT_FD_DUP)
		fd_dup(input, output, cmd);
	if (code & FT_FD_CLOSE)
		fd_close(input, output, cmd);
}
