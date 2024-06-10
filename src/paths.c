/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:42:56 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/10 12:34:25 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

is_path_absolute(char *path)
{
	return (path[0] == '/');
}

is_path_relative(char *path)
{
	return (path[0] == '.' && path[1] == '/');
}
