/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:37:37 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 23:33:44 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "px_types.h"


void		px_validate_input(int argc, char **argv);
void        px_cmd(t_process *process, char **env);
void		perror_msg(char *msg);
int			process_child(int *fd_input, int *fd_output, char *command, char **env);
void		fd_close(int *fd);
char const	*ft_str__find(char **env, char *key);
void		ft_split__free(char **strs);

#endif