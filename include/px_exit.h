/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:33:45 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 00:06:00 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_EXIT_H

# define PX_EXIT_H

# include "px_types.h"

# define FREE_PROGRAM 1
# define FREE_CMD 2
# define FREE_PROCESS 3
# define FREE_NONE 0

# define PX_EXIT_FAILURE -1
# define PX_EXIT_SUCESS 0
# define PX_EXIT 1
# define PX_EXIT_127 3
# define PX_EXIT_126 4
# define PX_EXIT_127__ENOENT 5

void	px_perror(const char *msg);
void	px_perror__127(char *msg);
void	px_free(t_program *program, t_process *process);
void	px_program__free(t_program *program);
void	px_process__free(t_process *process);
void	px_perror__generic(const char *msg, int exit_code);
void	px_exit__generic(const char *msg,
			void *mem_to_free, int type, int exit_code);

#endif