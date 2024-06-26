/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:34:56 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/19 23:34:08 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_FD_H
# define PX_FD_H

# include "../include/px_types.h"

void	px_close__program(int *fd,
			t_program *program, t_process *process);
void	px_close__cmd(int *fd, t_cmd *cmd);
void	px_close__program_full(int fd[2],
			t_program *program, t_process *process);

#endif