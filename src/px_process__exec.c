/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process__exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:17:20 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 06:10:11 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/px_exit.h"
#include "../include/px_types.h"
#include "../include/px_program.h"
#include "../include/px_cmd.h"

static void	initialize(t_cmd *cmd, t_program *program, char *cmdname)
{
	t_process	*process;

	process = content(program);
	cmd->input[0] = process->input[0];
	cmd->input[1] = process->input[1];
	cmd->output[0] = process->output[0];
	cmd->output[1] = process->output[1];
	cmd->env = program->env;
	cmd->str = cmdname;
	cmd->path = NULL;
	cmd->arr = NULL;
	cmd->possible_paths = NULL;
}

void	px_process__exec(t_program *program, char *cmdname)
{
	t_cmd		cmd;

	initialize(&cmd, program, cmdname);
	px_program__free(program);
	px_cmd__exec(&cmd);
}
