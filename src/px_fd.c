/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:37:59 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/16 10:13:44 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/px_types.h"
#include "../include/pipex.h"
#include "../include/px_exit.h"
#include <stdio.h>

void	px_close__check(int fd)
{
	if (fd < 0)
		return ;
	printf("closing fd = %d\n", fd);
	if (close(fd) == -1)
		px_perror("close");
	return ;
}

void	px_close__full(int (*fd)[2])
{
	px_close__check((*fd)[0]);
	px_close__check((*fd)[1]);
	(*fd)[0] = -1;
	(*fd)[1] = -1;
}
