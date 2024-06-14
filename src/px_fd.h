/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:34:56 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 23:27:29 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_FD_H
# define PX_FD_H

void	px_pipes_fd(int *fd_input, int *fd_output, int code);
void	px_close__check(int fd);
void	fd_close(int *fd);

#endif