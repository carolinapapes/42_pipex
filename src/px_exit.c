/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:29:13 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 00:24:45 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "pipex.h"
#include "px_process.h"
#include "px_types.h"
#include "px_program.h"
#include <stdio.h>
#include <errno.h>

// move this function to utils or px_free file
void	cmd__free(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->arr)
		ft_split__free(cmd->arr);
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	cmd = NULL;
}

void	process__free(t_process *process)
{
	if (!process)
		return ;
	if (process->cmd)
		cmd__free(process->cmd);
	free(process);
	process = NULL;
}

void	program__free(t_program *program)
{
	if (!program)
		return ;
	if (program->cmdv)
	{
		free(program->cmdv);
		program->cmdv = NULL;
	}
	if (program->list)
		ft_lstclear(&(program->list), (void *)process__free);
	program->list = NULL;
}

void	px_exit(char *msg, t_program *program, t_process *process)
{
	if (errno == 13)
		error_cmd_404(msg);
	else
		perror_msg(msg);
	process__free(process);
	program__free(program);
	if (errno == 13)
		exit (126);
	exit (errno);
}
