/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:49:35 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 00:23:07 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "unistd.h"
#include "../libs/libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/px_types.h"

static char	*error__127(char *command)
{
	char	*error_message;
	char	*error_message_2;

	error_message = ft_strjoin(command, ": ");
	if (!error_message)
		return (": command not found\n");
	error_message_2 = ft_strdup(error_message);
	if (!error_message_2)
		return (free(error_message), command);
	error_message = ft_strjoin(error_message, "command not found\n");
	if (!error_message)
		return (free(error_message_2), command);
	return (free(error_message_2), error_message);
}

static char	*get_error(char *msg)
{
	char	*error_message;
	char	*error_message_2;

	if (!msg)
	{
		error_message = ft_strdup(PROG_NAME);
		if (!error_message)
			return (PROG_NAME);
		return (PROG_NAME);
	}
	error_message = ft_strjoin(PROG_NAME, ": ");
	if (!error_message)
		return (PROG_NAME);
	error_message_2 = ft_strdup(error_message);
	if (!error_message_2)
		return (free(error_message), PROG_NAME);
	error_message = ft_strjoin(error_message, msg);
	if (!error_message)
		return (free(error_message_2), PROG_NAME);
	return (free(error_message_2), error_message);
}

void	px_perror(char *msg)
{
	char	*error_message;

	error_message = get_error(msg);
	perror(error_message);
	free(error_message);
	return ;
}

void px_perror__127(char *msg)
{
	ft_putstr_fd(get_error((error__127(msg))), 2);
	return ;
};