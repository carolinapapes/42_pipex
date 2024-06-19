/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_program__utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:26:11 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/19 21:26:29 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/pipex.h"
#include "../include/px_fd.h"
#include "../include/px_types.h"
#include "../include/px_program.h"
#include <stdio.h>

t_process	*content(t_program *program)
{
	if (!program->list || !program->list->content)
		return (NULL);
	return ((t_process *)program->list->content);
}

int	is_child(t_program *program)
{
	return (!(content(program)->pid));
}

int	(*get_fd(t_program *program, int fd))[2]
{
	if (fd == FT_FD_INPUT)
		return (&(content(program)->input));
	if (fd == FT_FD_OUTPUT)
		return (&(content(program)->output));
	return (NULL);
}

int	is_lastcmdv(t_program *program)
{
	return (!(program->cmdv[1]));
}
