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

#include <fcntl.h>
#include <unistd.h>
#include "../libs/libft/libft.h"
#include "files_fd.h"
#include "pipex.h"

static void	input_set__first(t_process *first, char *file)
{
	first->input[WRITE_END] = -1;
	first->input[READ_END] = open(file, O_RDONLY);
	if (first->input[READ_END] == -1)
		perror_msg(file);
	return ;
}

static void	input_set__nonfirst(t_list *list, t_process *current)
{
	t_process	*second;

	second = (t_process *)list->next->content;
	current->input[READ_END] = second->output[READ_END];
	current->input[WRITE_END] = second->output[WRITE_END];
	return ;
}

static void	output_set__last(t_process *last, char *file)
{
	last->output[READ_END] = -1;
	last->output[WRITE_END] = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (last->output[WRITE_END] == -1)
		perror_msg(file);
	return ;
}

static void	output_set__nonlast(t_process *current)
{
	if (pipe(current->output) < 0)
		perror_msg("pipe");
}

void	io_set(t_list *list, char *file, int is_last)
{
	t_process	*current;

	current = (t_process *)list->content;
	if (!list->next)
		input_set__first(current, file);
	else
		input_set__nonfirst(list, current);
	if (is_last)
		output_set__last(current, file);
	else
		output_set__nonlast(current);
	return ;
}