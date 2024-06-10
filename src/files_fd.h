/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_fd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:34:56 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/09 09:38:11 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_FD_H
# define FILES_FD_H

# define READ_END 0
# define WRITE_END 1

# define FT_FD_INIT 1
# define FT_FD_ERROR 2
# define FT_FD_DUP 4
# define FT_FD_CLOSE 8

void	process_fds(int *fd_input, int *fd_output, int code);

#endif