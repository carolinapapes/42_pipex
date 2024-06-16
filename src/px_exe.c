/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:26:02 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 09:36:10 by carolinapap      ###   ########.fr       */
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

void	px_child__init(t_process **process, t_program *program, t_list **list)
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

	px_child__init(&process, program, list);
	px_fd__handler(process->input, process->output, FT_FD_INIT | FT_FD_DUP);
	if (process->input[READ_END] >= 0)
		px_cmd(cmd, program->env);
	px_fd__handler(process->input, process->output, FT_FD_CLOSE);
	exit(1);
}

/**
 * BRIEF: Executes the commands in the program
 * 
 * Exec will create a list of all the processes to be executed.
 * Each process consist in a command to be executed and the input and output fds.
 * The list will be iterated and each process will be executed in a forked process.
 * The main will only mantain a list of pids and will wait for all of them to finish.
 * Also the input and output file descriptors of each process will be closed.
 * 
 * @param program: The program to be executed
 * @return int: 0 if the program was executed successfully
 * 
 * ALLOCATED: program->cmdv, list, list->content(process);
 */

void	close_pipes(t_list *list, t_program *program)
{
	px_close__full(&(content(list)->input));
	if (!(program->cmdv[1]))
		px_close__full(&content(list)->output);
}

int	px_exec(t_program *program)
{
	t_list		*list;
	char		**cmdv;

	list = NULL;
	cmdv = program->cmdv;
	while (cmdv[0])
	{
		px_process(&list, program);
		px_fd__set(list, program->fd_names, !cmdv[1]);
		px_process__fork(content(list));
		if (content(list)->pid == 0)
			px_child(program, cmdv[0], &list);
		close_pipes(list, program);
		cmdv++;
	}
	ft_lstiter(list, (void *)px_process__wait);
	ft_lstclear(&list, (void *)px_process__free);
	return (0);
}

// replace i by cmdc
// remove list and add it to program structure
// remove input params from process