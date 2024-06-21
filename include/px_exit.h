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

void	px_exit(char *msg, t_program *program);
void	px_exit__cmd(const char *msg, t_cmd *cmd);
void	px_exit__127(char *msg, t_cmd *cmd);
void	px_exit__126(char *msg, t_cmd *cmd);
void	px_perror(char *msg);
void	px_perror__127(char *msg);
void	px_free(t_program *program, t_process *process);
void	px_program__free(t_program *program);
void	px_process__free(t_process *process);

#endif