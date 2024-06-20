/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process__fork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:18:28 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 23:57:28 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include "../include/px_exit.h"
#include "../include/px_types.h"

void	px_process__fork(t_process *process, t_program *program)
{
	process->pid = fork();
	if (process->pid == -1)
		px_exit("fork", program);
}
