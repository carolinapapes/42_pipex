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

#include "pipex.h"
#include "../libs/libft/libft.h"

static void	process_init(t_process **process)
{
	(*process)->pid = -1;
	(*process)->input[0] = -1;
	(*process)->input[1] = -1;
	(*process)->output[0] = -1;
	(*process)->output[1] = -1;
	return ;
}

static void	ft_allocate_process(t_process **process)
{
	*process = (t_process *)malloc(sizeof(t_process));
	if (!(*process))
		perror_msg("malloc");
	return ;
}

t_process	*create_process(t_list **list)
{
	t_process	*process;

	ft_allocate_process(&process);
	process_init(&process);
	ft_lstadd_front(list, ft_lstnew((void *)process));
	return (process);
}
