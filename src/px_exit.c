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
#include "../include/px_exit.h"
#include "../include/pipex.h"
#include "../include/px_process.h"
#include "../include/px_types.h"
#include "../include/px_program.h"
#include <stdio.h>
#include <errno.h>

// move this function to utils or px_free file
static void	cmd__free(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->arr)
	{
		ft_split__free(cmd->arr);
		cmd->arr = NULL;
	}
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
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

void	px_free(t_program *program, t_process *process)
{
	process__free(process);
	program__free(program);
}

void	px_exit(char *msg, t_program *program, t_process *process)
{
	int err;

	err = errno;
	ft_putnbr_fd(err, 2);
	ft_putstr_fd("\n", 2);
	px_perror(msg);
	px_free(program, process);
	exit(err);
}

void	px_exit__127(char *msg, t_program *program, t_process *process)
{
	px_perror__127(msg);
	px_free(program, process);
	exit(127);
}

void	px_exit__126(char *msg, t_program *program, t_process *process)
{
	px_perror(msg);
	px_free(program, process);
	exit(126);
}

