/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:09:09 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 00:47:54 by carolinapap      ###   ########.fr       */
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

int	is_first_item(t_list *list)
{
	if (!list->next)
		return (1);
	return (0);
}

void	*ft_lst_beforelast(t_list *list)
{
	t_list	*tmp;

	if (!list || !list->next)
		return (NULL);
	tmp = list;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	return (tmp->content);
}

void	input_set__first(t_process *first, char *file)
{
	first->input[WRITE_END] = -1;
	first->input[READ_END] = open(file, O_RDONLY);
	if (first->input[READ_END] == -1)
		perror_msg(file);
	return ;
}

void	input_set__nonfirst(t_list *list, t_process *last)
{
	t_process	*beforelast;

	beforelast = (t_process *)ft_lst_beforelast(list);
	last->input[READ_END] = beforelast->output[READ_END];
	last->input[WRITE_END] = beforelast->output[WRITE_END];
	return ;
}

void	input_set(t_list *list, t_process *current, char *file, int is_first)
{
	if (is_first)
		input_set__first(current, file);
	else
		input_set__nonfirst(list, current);
	return ;
}
