/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:37:37 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/20 00:27:43 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../include/px_types.h"

char const	*ft_str__find(char **env, char *key);
void		ft_split__free(char **strs);
void		px_cmd__exec(t_cmd *cmd);
void		px_validate_input(int argc, char **argv);
void		px_cmd__fd(t_cmd *cmd, int code);
void		is_dir(char *name);
char		*is_path(char *name, char **path);

#endif