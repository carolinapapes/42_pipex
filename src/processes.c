/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:09:09 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/12 22:13:39 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libs/libft/libft.h"

static void	px_process__init(t_process **process)
{
	(*process)->pid = -1;
	(*process)->input[0] = -1;
	(*process)->input[1] = -1;
	(*process)->output[0] = -1;
	(*process)->output[1] = -1;
	return ;
}

static void	px_process__allocate(t_process **process)
{
	*process = (t_process *)malloc(sizeof(t_process));
	if (!(*process))
		perror_msg("malloc");
	return ;
}

t_process	*px_process(t_list **list)
{
	t_process	*process;

	px_process__allocate(&process);
	px_process__init(&process);
	ft_lstadd_front(list, ft_lstnew((void *)process));
	return (process);
}
