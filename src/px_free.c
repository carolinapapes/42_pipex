/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:14:03 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/19 22:14:05 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../include/px_exit.h"
#include "../include/pipex.h"
#include "../include/px_process.h"
#include "../include/px_types.h"
#include "../include/px_program.h"
#include <stdio.h>
#include <errno.h>

void	cmd__free(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->arr)
		ft_split__free(cmd->arr);
	if (cmd->path)
		ft_free(cmd->path);
}

static void	process__free(t_process *process)
{
	if (!process)
		return ;
	if (process->cmd)
		cmd__free(process->cmd);
	free(process);
	process = NULL;
}

void	px_program__free(t_program *program)
{
	if (!program)
		return ;
	if (program->cmdv)
		ft_free(program->cmdv);
	if (program->list)
		ft_lstclear(&(program->list), (void *)process__free);
	program->list = NULL;
}

void	px_free(t_program *program, t_process *process)
{
	process__free(process);
	px_program__free(program);
}
