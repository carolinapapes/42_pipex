/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:39:15 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 00:04:38 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_CMD_H

# define PX_CMD_H

# include "px_types.h"

void	px_cmd__exec(t_cmd *cmd);
void	px_cmd__fd(t_cmd *cmd, int code);
void	cmd__path(t_cmd *cmd);
void	px_cmd__free(t_cmd *cmd);

#endif