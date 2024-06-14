/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:45:31 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 22:54:17 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../libs/libft/libft.h"
#include "px_fd.h"
#include "px_types.h"
#include "pipex.h"

static void	input_set(t_list *list, t_process *current)
{
	t_process	*prev;

	prev = (t_process *)list->next->content;
	current->input[READ_END] = prev->output[READ_END];
	current->input[WRITE_END] = prev->output[WRITE_END];
	return ;
}

static void	input_set__first(t_process *current, char *file)
{
	current->input[WRITE_END] = -1;
	current->input[READ_END] = open(file, O_RDONLY);
	if (current->input[READ_END] == -1)
		perror_msg(file);
	return ;
}

static void	output_set(t_process *current)
{
	if (pipe(current->output) < 0)
		perror_msg("pipe");
}

static void	output_set__last(t_process *current, char *file)
{
	current->output[READ_END] = -1;
	current->output[WRITE_END] = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (current->output[WRITE_END] == -1)
		perror_msg(file);
	return ;
}

void	io_set(t_list *list, char *file[2], int is_last)
{
	t_process	*current;

	current = (t_process *)list->content;
	if (list->next)
		input_set(list, current);
	else
		input_set__first(current, file[READ_END]);
	if (!is_last)
		output_set(current);
	else
		output_set__last(current, file[WRITE_END]);
	return ;
}
