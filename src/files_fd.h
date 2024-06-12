/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_fd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:34:56 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 23:56:30 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_FD_H
# define FILES_FD_H
# include "../libs/libft/libft.h"
# include "pipex.h"
# define READ_END 0
# define WRITE_END 1

# define FT_FD_INIT 1
# define FT_FD_ERROR 2
# define FT_FD_DUP 4
# define FT_FD_CLOSE 8

# define IS_FIRST_PROCESS 1
# define IS_LAST_PROCESS 2

void	process_fds(int *fd_input, int *fd_output, int code);
#endif