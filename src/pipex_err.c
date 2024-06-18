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

#include "pipex.h"
#include "unistd.h"
#include "../libs/libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "px_types.h"

char	*error_cmd_404(char *command)
{
	char	*error_message;
	char	*error_message_2;

	error_message = ft_strjoin(command, ": ");
	if (!error_message)
		return (": command not found\n");
	error_message_2 = ft_strdup(error_message);
	if (!error_message_2)
		return (free(error_message), command);
	error_message = ft_strjoin(error_message, ": command not found\n");
	if (!error_message)
		return (free(error_message_2), command);
	return (free(error_message_2), error_message);
}

char	*get_error(char *msg)
{
	char	*error_message;
	char	*error_message_2;

	if (!msg)
		return (PROG_NAME);
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

void	perror_msg(char *msg)
{
	char	*error_message;

	error_message = get_error(msg);
	perror(error_message);
	free(error_message);
	return ;
}

// void	perror_cmd_msg(char *msg)
// {
// 	char	*error_message;

// 	error_message = get_error(msg);
// 	error_message = error_cmd_404(error_message);
// 	ft_putstr_fd(error_message, STDERR_FILENO);
// 	free(error_message);
// 	return ;
// }




// char	*error_cmd_is_dir(char *command)
// {
// 	char	*error_message;
// 	char	*error_message_2;
// 	char	*error_message_3;

// 	error_message_3 = ft_strjoin(PROG_NAME, ": ");
// 	if (!error_message_3 || !command)
// 		return (": Is a directory\n");
// 	error_message = ft_strjoin(command, ": ");
// 	if (!error_message)
// 		return (": Is a directory\n");
// 	error_message_2 = ft_strjoin(error_message_3, error_message);
// 	if (!error_message_2)
// 		return (free(error_message), free(error_message_3), \
// 			": Is a directory\n");
// 	return (free(error_message), free(error_message_3), error_message_2);
// }
