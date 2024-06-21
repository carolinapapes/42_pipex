/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:49:35 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 22:46:15 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "../libs/libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/px_types.h"

static char	*get_program(void)
{
	char	*name;

	name = ft_strdup(PROG_NAME);
	return (name);
}

static char	*error__127(char *command)
{
	char	*base_message;
	char	*error_message;
	char	*tmp;

	base_message = ft_strdup("command not found\n");
	if (!command)
		return (base_message);
	tmp = ft_strjoin(command, ": ");
	if (!tmp)
		return (base_message);
	error_message = ft_strjoin(tmp, base_message);
	free(tmp);
	if (!error_message)
		return (base_message);
	free(base_message);
	return (error_message);
}

static char	*get_error(char *msg)
{
	char	*program_name;
	char	*error_message;
	char	*tmp;

	program_name = get_program();
	if (!msg)
		return (program_name);
	tmp = ft_strjoin(program_name, ": ");
	if (!tmp)
		return (program_name);
	error_message = ft_strjoin(tmp, msg);
	free(tmp);
	if (!error_message)
		return (program_name);
	free(program_name);
	return (error_message);
}

static char	*get_error__generic(const char *msg)
{
	char	*program_name;
	char	*error_message;
	char	*tmp;

	program_name = get_program();
	if (!msg)
		return (program_name);
	tmp = ft_strjoin(program_name, ": ");
	if (!tmp)
		return (program_name);
	error_message = ft_strjoin(tmp, msg);
	free(tmp);
	if (!error_message)
		return (program_name);
	free(program_name);
	return (error_message);
}

void	px_perror__generic(const char *msg)
{
	char	*error_message;

	error_message = get_error__generic(msg);
	perror(error_message);
	free(error_message);
	return ;
}

void	px_perror(char *msg)
{
	char	*error_message;

	error_message = get_error(msg);
	perror(error_message);
	free(error_message);
	return ;
}

void	px_perror__127(char *msg)
{
	char	*error_message;
	char	*tmp;

	tmp = error__127(msg);
	error_message = get_error(tmp);
	free(tmp);
	ft_putstr_fd(error_message, 2);
	free(error_message);
	return ;
}
