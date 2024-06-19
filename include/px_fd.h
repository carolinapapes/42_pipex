/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:34:56 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 21:34:30 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_FD_H
# define PX_FD_H

# include "../include/px_types.h"

void	px_fd__handler(t_process *process, int code);
void	px_close__check(int fd, t_program *program, t_process *process);
void	px_close__full(int (*fd)[2], t_program *program, t_process *process);

#endif