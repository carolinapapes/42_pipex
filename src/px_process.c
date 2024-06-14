/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:09:09 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 22:54:01 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"
#include "pipex.h"
#include "px_process.h"
#include "px_types.h"

// must check list allocation malloc
void	px_process(t_list **list)
{
	t_process	*process;
	t_list		*item;

	px_process__allocate(&process);
	px_process__init(process);
	item = ft_lstnew((void *)process);
	if (!item)
	{
		perror_msg("list item allocation failed");
		px_process__free(process);
		ft_lstclear(list, (void *)px_process__free);
		exit(1);
	}
	ft_lstadd_front(list, item);
	return ;
}
