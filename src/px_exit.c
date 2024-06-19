/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:29:13 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 22:37:45 by carolinapap      ###   ########.fr       */
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

void	px_exit(char *msg, t_program *program, t_process *process)
{
	int	err;

	err = errno;
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
