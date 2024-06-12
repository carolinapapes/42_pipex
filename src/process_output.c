/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:45:31 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 01:05:52 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include "../libs/libft/libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include "files_fd.h"

void	output_set__last(t_process *last, char *file)
{
	last->output[READ_END] = -1;
	last->output[WRITE_END] = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (last->output[WRITE_END] == -1)
		perror_msg(file);
	return ;
}

void	output_set__nonlast(t_process *current)
{
	if (pipe(current->output) < 0)
		perror_msg("pipe");
}

void	output_set(t_process *current, char *file, int is_last)
{
	if (is_last)
		output_set__last(current, file);
	else
		output_set__nonlast(current);
	return ;
}
