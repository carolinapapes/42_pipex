/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:28:09 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 23:34:00 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_PROCESS_H

# define PX_PROCESS_H
# include "../libs/libft/libft.h"
# include "px_types.h"


void		px_process__init(t_program *program);
void		px_process__fork(t_process *process, t_program *program);
void        px_process__fd_open(t_program *program, int is_last);
void		px_process__fd_close(t_program *program);
void		px_process__wait(t_program *program);
void		px_process__exec(t_program *program, char *cmd);

#endif