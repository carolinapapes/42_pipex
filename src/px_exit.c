/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:29:13 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 00:08:10 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../include/px_exit.h"
#include "../include/px_process.h"
#include "../include/px_types.h"
#include "../include/px_program.h"
#include "../include/px_cmd.h"
#include <stdio.h>
#include <errno.h>

void	px_exit(char *msg, t_program *program)
{
	int	err;

	err = errno;
	px_perror(msg);
	px_free(program, NULL);
	exit(err);
}

# define FREE_PROGRAM 1
# define FREE_CMD 2
# define FREE_PROCESS 3

void	px_free_generic(void *mem_to_free, int type)
{
	if (type == FREE_PROGRAM)
		px_program__free((t_program *)mem_to_free);
	else if (type == FREE_CMD)
		px_cmd__free((t_cmd *)mem_to_free);
	else if (type == FREE_PROCESS)
		px_process__free((t_process *)mem_to_free);
}

void	px_exit__generic(const char *msg, void *mem_to_free, int type)
{
	int	err;

	err = errno;
	px_perror(msg);
	px_free_generic(mem_to_free, type);
	exit(err);
}

void	px_exit__cmd(const char *msg, t_cmd *cmd)
{
	int	err;

	err = errno;
	px_perror((char *)msg);
	px_cmd__free(cmd);
	exit(err);
}

void	px_exit__127(char *msg, t_cmd *cmd)
{
	px_perror__127(msg);
	px_cmd__free(cmd);
	exit(127);
}

void	px_exit__126(char *msg, t_cmd *cmd)
{
	px_perror(msg);
	px_cmd__free(cmd);
	exit(126);
}
