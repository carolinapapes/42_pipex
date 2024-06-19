/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process__init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:09:09 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/19 14:51:21 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/px_types.h"
#include "../include/px_exit.h"


static void	allocate(t_program *program, t_process **process)
{
	*process = (t_process *)malloc(sizeof(t_process));
	if (!(*process))
		px_exit("Process allocation failed;", program, *process);
}

static void	initialize(t_process *process)
{
	process->pid = -1;
	process->input[0] = -1;
	process->input[1] = -1;
	process->output[0] = -1;
	process->output[1] = -1;
	process->cmd = NULL;
	return ;
}

static void	lstadd(t_program *program, t_process **process)
{
	t_list		*item;

	item = ft_lstnew((void *)(*process));
	if (!item)
		px_exit("Item allocation failed;", program, *process);
	ft_lstadd_front(&program->list, item);
}

/**
 * @brief Create a new process and add it to the list. 
 * If  allocation fails, the program will exit.
 * 
 * @param program The program structure that contains the list of processes.
 * 
 * ALLOCATED: program. list, process
 * EXIT ON: process allocation failed, item allocation failed
 */
void	px_process__init(t_program *program)
{
	t_process	*process;

	allocate(program, &process);
	initialize(process);
	lstadd(program, &process);
	return ;
}
