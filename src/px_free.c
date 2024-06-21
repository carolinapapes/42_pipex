/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:14:03 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 00:05:58 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/libft_exp.h"
#include "../libs/libft/libft_bonus.h"
#include "../include/px_types.h"

void	px_cmd__free(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->arr)
		ft_split__free(cmd->arr);
	if (cmd->path)
		ft_free(cmd->path);
	if (cmd->possible_paths)
		ft_split__free(cmd->possible_paths);
}

void	px_process__free(t_process *process)
{
	if (!process)
		return ;
	free(process);
	process = NULL;
}

void	px_program__free(t_program *program)
{
	if (!program)
		return ;
	if (program->cmdv)
		ft_free(program->cmdv);
	if (program->list)
		ft_lstclear(&(program->list), (void *)px_process__free);
	program->list = NULL;
}

void	px_free(t_program *program, t_process *process)
{
	px_process__free(process);
	px_program__free(program);
}
