/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:09:09 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 08:53:05 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "px_process.h"
#include "px_types.h"

// must check list allocation malloc

void	px_process__exit(char *msg, t_list **list, t_program *program, t_process *process)
{
	perror_msg(msg);
	if (process)
		px_process__free(process);
	ft_lstiter(*list, (void *)px_process__wait);
	ft_lstclear(list, (void *)px_process__free);
	free(program->cmdv);
	exit(1);
}

void	px_process__allocate(t_list **list, t_program *program, t_process **process)
{
	*process = (t_process *)malloc(sizeof(t_process));
	if (!process)
		px_process__exit("Process allocation failed;", list, program, *process);
}

void	px_process__lstadd(t_list **list, t_program *program, t_process **process)
{
	t_list		*item;

	item = ft_lstnew((void *)(*process));
	if (!item)
		px_process__exit("Item allocation failed;", list, program, *process);
	ft_lstadd_front(list, item);
}

void	px_process__init(t_process *process)
{
	process->pid = -1;
	process->input[0] = -1;
	process->input[1] = -1;
	process->output[0] = -1;
	process->output[1] = -1;
	return ;
}

/**
 * @brief Create a new process and add it to the list. If  allocation fails, the program will exit.
 * 
 * 
 * @param list			Pointer to list of processes, if dont exist will be created.
 * @param program		Pointer to program for exit propourses.
 * 
 * ALLOCATED: program. list, process
 * EXIT ON: process allocation failed, item allocation failed
 */
void	px_process(t_list **list, t_program *program)
{
	t_process	*process;

	px_process__allocate(list, program, &process);
	px_process__init(process);
	px_process__lstadd(list, program, &process);
	return ;
}


	// printf("item created\n");
	// printf("process: %p\n", *process);
	// printf("process->pid: %d\n", (*process)->pid);
	// printf("process->input[0]: %d\n", (*process)->input[0]);
	// printf("process->input[1]: %d\n", (*process)->input[1]);
	// printf("process->output[0]: %d\n", (*process)->output[0]);
	// printf("process->output[1]: %d\n", (*process)->output[1]);
	// printf("list: %p\n", *list);
	// printf("program: %p\n", program);