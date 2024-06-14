/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:37:59 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 22:52:20 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "px_types.h"
#include "pipex.h"

void	px_close__check(int fd)
{
	if (fd < 0)
		return ;
	if (close(fd) == -1)
		perror_msg("close");
	return ;
}

void	fd_close(int *fd)
{
	px_close__check(fd[READ_END]);
	px_close__check(fd[WRITE_END]);
}
