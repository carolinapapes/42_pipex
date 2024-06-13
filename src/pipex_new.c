/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:45:38 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 00:11:34 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "../libs/libft/libft.h"
#include "pipex.h"
#include "px_fd.h"
#include "px_process.h"
#include "px_program.h"

void	px_process__wait(t_process *process)
{
	waitpid(process->pid, NULL, 0);
}

void	px_child(t_process *process, char *command, char **env)
{
	px_pipes_fd(process->input, process->output, FT_FD_INIT | FT_FD_DUP);
	if (process->input[READ_END] >= 0)
		px_cmd(command, env);
	px_pipes_fd(process->input, process->output, FT_FD_CLOSE);
	exit(0);
}

void	px_process__fork(t_process *process)
{
	process->pid = fork();
	if (process->pid == -1)
		perror_msg("fork");
}

t_process *content(t_list *lst)
{
	return ((t_process *)lst->content);
}

int	pipex_new(t_program *program)
{
	int			i;
	t_list		*list;

	i = -1;
	list = NULL;
	while (++i < program->cmdc)
	{
		px_process(&list);
		io_set(list, program->fd_names, i == program->cmdc - 1);
		fork_process(content(list));
		if (content(list)->pid == 0)
			px_child(content(list), program->cmdv[i], program->env);
		fd_close(content(list)->input);
	}
	fd_close(content(list)->output);
	ft_lstiter(list, (void *)px_process__wait);
	return (0);
}
