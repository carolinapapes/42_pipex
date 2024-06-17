/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:28:09 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 11:14:22 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_PROCESS_H

# define PX_PROCESS_H
# include "../libs/libft/libft.h"
# include "px_types.h"

void	px_process__init(t_program *program);
void	px_process__free(void *process);
void	px_process__fork(t_process *process);
void	px_process__wait(t_process *process);
void	px_process__fd_open(t_list *list, char *file[2], int is_last);
void	px_process__exit(char *msg, t_program *program, t_process *process);

#endif