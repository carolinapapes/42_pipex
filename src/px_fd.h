/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:34:56 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 10:14:01 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_FD_H
# define PX_FD_H

void	px_fd__handler(int *fd_input, int *fd_output, int code);
void	px_close__check(int fd);
void	px_close__full(int (*fd)[2]);

#endif