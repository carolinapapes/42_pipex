/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_program_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:45:16 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 23:45:17 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"
#include "px_fd.h"
#include "px_types.h"
#include "px_process.h"
#include "../libs/libft/libft.h"

void	px_child(t_process *process, char *command, char **env)
{
	px_pipes_fd(process->input, process->output, FT_FD_INIT | FT_FD_DUP);
	if (process->input[READ_END] >= 0)
		px_cmd(command, env);
	px_pipes_fd(process->input, process->output, FT_FD_CLOSE);
	exit(0);
}

t_process	*content(t_list *lst)
{
	return ((t_process *)lst->content);
}

int	px_exec(t_program *program)
{
	int			i;
	t_list		*list;

	i = -1;
	list = NULL;
	while (++i < program->cmdc)
	{
		px_process(&list);
		io_set(list, program->fd_names, i == program->cmdc - 1);
		px_process__fork(content(list));
		if (content(list)->pid == 0)
			px_child(content(list), program->cmdv[i], program->env);
		fd_close(content(list)->input);
	}
	fd_close(content(list)->output);
	ft_lstiter(list, (void *)px_process__wait);
	return (0);
}