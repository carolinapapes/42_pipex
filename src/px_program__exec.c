/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:26:02 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 23:33:45 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/px_types.h"
#include "../include/px_process.h"
#include "../include/px_program.h"

/**
 * @brief Launch all process and wait for them to finish
 */
void	px_program__exec(t_program *program)
{
	char		**cmdv;

	cmdv = program->cmdv;
	while (cmdv[0])
	{
		px_process__init(program);
		px_process__fd_open(program, !cmdv[1]);
		px_process__fork(content(program), program);
		if (is_child(program))
			px_process__exec(program, cmdv[0]);
		px_process__fd_close(program);
		cmdv++;
	}
	px_process__wait(program);
}
