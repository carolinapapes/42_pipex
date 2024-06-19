/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process__fd_close.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:33:47 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/19 22:35:21 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/px_fd.h"
#include "../include/px_types.h"
#include "../include/px_process.h"
#include "../include/px_program.h"

void	px_process__fd_close(t_program *program)
{
	px_close__full(get_fd(program, FT_FD_INPUT), program, NULL);
	if (is_lastcmdv(program))
		px_close__full(get_fd(program, FT_FD_OUTPUT), program, NULL);
}
