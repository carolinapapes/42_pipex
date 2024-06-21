/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:18:11 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 11:08:19 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../include/px_cmd.h"
#include "../include/pipex.h"
#include "../include/px_types.h"
#include "../include/px_process.h"
#include "../include/px_exit.h"
#include "../include/libft_exp.h"

static void	get__arr(t_cmd *cmd, char separator)
{
	cmd->arr = ft_split(cmd->str, separator);
	if (!(cmd->arr))
		px_exit__cmd(who(__func__), cmd);
	if (!cmd->arr[0])
		px_exit__127("", cmd);
}

void	px_cmd__exec(t_cmd *cmd)
{
	px_cmd__fd(cmd, FT_FD_OPEN);
	get__arr(cmd, ' ');
	cmd__path(cmd);
	execve(cmd->path, cmd->arr, cmd->env);
	px_cmd__fd(cmd, FT_FD_CLOSE);
	px_exit__126(cmd->path, NULL);
}
