/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:27:50 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 23:37:24 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"
#include "files_fd.h"
#include <stdlib.h>
#include <stdio.h>

int	process_child(int *fd_read, int *fd_output, char *command, char **env)
{
	int	i;

	px_pipes_fd(fd_read, fd_output, FT_FD_INIT | FT_FD_ERROR | FT_FD_DUP);
	i = px_cmd(command, env);
	px_pipes_fd(fd_read, fd_output, FT_FD_CLOSE);
	exit(i);
}
