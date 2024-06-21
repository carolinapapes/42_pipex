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
#include "../include/libft_exp.h"
#include "../include/px_cmd.h"
#include "../include/px_exit.h"
#include "../include/px_types.h"

static void	get__arr(t_cmd *cmd, char separator)
{
	cmd->arr = ft_split(cmd->str, separator);
	if (!(cmd->arr))
		px_exit__generic(who(__func__), cmd, FREE_CMD, PX_EXIT_FAILURE);
	if (!cmd->arr[0])
		px_exit__generic(cmd->arr[0], cmd, FREE_CMD, PX_EXIT_127);
}

void	px_cmd__exec(t_cmd *cmd)
{
	px_cmd__fd(cmd, FT_FD_OPEN);
	get__arr(cmd, ' ');
	cmd__path(cmd);
	execve(cmd->path, cmd->arr, cmd->env);
	px_cmd__fd(cmd, FT_FD_CLOSE);
	px_exit__generic(cmd->path, cmd, FREE_CMD, PX_EXIT_126);
}
