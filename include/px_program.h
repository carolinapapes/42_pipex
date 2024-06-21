/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_program.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:28:32 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 00:06:58 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_PROGRAM_H

# define PX_PROGRAM_H
# include "px_types.h"

int		is_child(t_program *program);
int		is_lastcmdv(t_program *program);
void	px_program__init(t_program *program, int argc, char **argv, char **env);
void	px_program__exec(t_program *program);
void	px_program__free(t_program *program);

#endif
