/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process__exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:17:20 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/19 22:15:24 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/px_exit.h"
#include "../include/px_fd.h"
#include "../include/px_types.h"
#include "../include/px_process.h"
#include "../include/px_program.h"

void	exec__clean( t_process **process, t_program **program, char *cmd)
{
	*process = content(*program);
	(*program)->list->content = NULL;
	(*process)->cmd = NULL;
	(*process)->cmd_str = cmd;
	px_program__free(*program);
}

void	px_process__exec(t_program *program, char *cmd)
{
	t_process	*process;

	exec__clean(&process, &program, cmd);
	px_cmd__fd(process, FT_FD_OPEN);
	px_cmd(process, program->env);
	px_cmd__fd(process, FT_FD_CLOSE);
	px_exit(cmd, program, process);
}
