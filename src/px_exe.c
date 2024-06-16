/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:26:02 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 11:05:22 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"
#include "px_fd.h"
#include "px_types.h"
#include "px_process.h"

#include <stdio.h>

t_process	*content(t_list *lst)
{
	return ((t_process *)lst->content);
}

void	px_child__clean(t_process **process, t_program *program, t_list **list)
{
	*process = content(*list);
	(*list)->content = NULL;
	ft_lstclear(list, (void *)px_process__free);
	free(program->cmdv);
}

// void	px_child(t_process *process, char *command, char **env)
void	px_child(t_program *program, char *cmd, t_list **list)
{
	t_process	*process;

	px_child__clean(&process, program, list);
	px_fd__handler(process->input, process->output, FT_FD_INIT | FT_FD_DUP);
	if (process->input[READ_END] >= 0)
		px_cmd(cmd, program->env);
	px_fd__handler(process->input, process->output, FT_FD_CLOSE);
	exit(1);
}

/**
 * BRIEF: Executes the commands in the program
 * 
 * Each iteration will:
 * create a process
 * open FDs (pipes or files)
 * fork the process
 * in child process:
 * 	 execute the comand
 * in parente process:
 * 	 close the pipes
 * 	 wait for the child process to finish
 *	 free the process
 * 
 * @param program: The program to be executed
 * @return int: 0 if the program was executed successfully
 * 
 * ALLOCATED: program->cmdv, list, list->content(process);
 */

void	px_process__fd_close(t_list *list, t_program *program)
{
	px_close__full(&(content(list)->input));
	if (!(program->cmdv[1]))
		px_close__full(&content(list)->output);
}

int	px_process(t_program *program)
{
	char		**cmdv;

	cmdv = program->cmdv;
	while (cmdv[0])
	{
		px_process__init(program);
		px_process__fd_open(program->list, program->fd_names, !cmdv[1]);
		px_process__fork(content(program->list));
		if (!(content(program->list)->pid))
			px_child(program, cmdv[0], &(program->list));
		px_process__fd_close(program->list, program);
		cmdv++;
	}
	ft_lstiter(program->list, (void *)px_process__wait);
	return (0);
}

// remove input params from process