/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process__fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:45:31 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 00:19:46 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/px_fd.h"
#include "../include/px_types.h"
#include "../include/px_exit.h"
#include "../include/px_process.h"


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
	current->input[READ_END] = open(file, O_RDONLY);
	if (current->input[READ_END] == -1)
		px_exit(file, NULL, current);

}

static void	output_set(t_process *current, t_program *program)
{
	if (pipe(current->output) < 0)
		px_exit("pipe", program, NULL);
}

static void	output_set__last(t_process *current, char *file, t_program *program)
{
	current->output[WRITE_END] = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (current->output[WRITE_END] == -1)
		px_exit(file, program, NULL);
	return ;
}

void	px_process__fd_open(t_program *program, int is_last)
{
	t_process	*current;

	current = (t_process *)program->list->content;
	if (program->list->next)
		input_set((t_list *)program->list, current);
	else
		input_set__first(current, (program->fd_names)[READ_END]);
	if (!is_last)
		output_set(current, program);
	else
		output_set__last(current, (program->fd_names)[WRITE_END], program);
}

void	px_process__fd_close(t_list *list, t_program *program)
{
	px_close__full(&(content(list)->input));
	if (!(program->cmdv[1]))
		px_close__full(&content(list)->output);
}
