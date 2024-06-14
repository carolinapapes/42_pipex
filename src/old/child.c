/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:27:50 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 23:24:28 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"
#include "px_fd.h"
#include "px_types.h"

int	process_child(int *fd_read, int *fd_output, char *command, char **env)
{
	int	i;

	px_pipes_fd(fd_read, fd_output, FT_FD_INIT | FT_FD_ERROR | FT_FD_DUP);
	i = px_cmd(command, env);
	px_pipes_fd(fd_read, fd_output, FT_FD_CLOSE);
	exit(i);
}
