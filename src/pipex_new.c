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



void	px_child(t_process *process, char *command, char **env)
{
	px_pipes_fd(process->input, process->output, FT_FD_INIT | FT_FD_DUP);
	if (process->input[READ_END] >= 0)
		px_cmd(command, env);
	px_pipes_fd(process->input, process->output, FT_FD_CLOSE);
	exit(0);
}



t_process *content(t_list *lst)
{
	return ((t_process *)lst->content);
}

