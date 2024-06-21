/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:29:13 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 00:08:10 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "../include/px_cmd.h"
#include "../include/px_exit.h"
#include "../include/px_types.h"

void	px_free_generic(void *mem_to_free, int type)
{
	if (type == FREE_PROGRAM)
		px_program__free((t_program *)mem_to_free);
	else if (type == FREE_CMD)
		px_cmd__free((t_cmd *)mem_to_free);
	else if (type == FREE_PROCESS)
		px_process__free((t_process *)mem_to_free);
}

void	px_perror__generic(const char *msg, int exit_code)
{
	if (exit_code == PX_EXIT_SUCESS)
		return ;
	if (exit_code == PX_EXIT_127)
		px_perror__127((char *)msg);
	else
		px_perror((char *)msg);
}

void	px_exit__status(int exit_code, int err)
{
	if (exit_code == PX_EXIT_SUCESS)
		exit(0);
	else if (exit_code == PX_EXIT)
		exit(1);
	else if (exit_code == PX_EXIT_126)
		exit(126);
	else if (exit_code == PX_EXIT_127 \
		|| exit_code == PX_EXIT_127__ENOENT)
		exit(127);
	else
		exit(err);
}

void	px_exit__generic(const char *msg,
			void *mem, int type, int exit_code)
{
	int	err;

	err = errno;
	px_perror__generic(msg, exit_code);
	px_free_generic(mem, type);
	px_exit__status(exit_code, err);
}
