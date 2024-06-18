/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:37:37 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/18 00:23:46 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../include/px_types.h"

char const	*ft_str__find(char **env, char *key);
void		ft_split__free(char **strs);
void		px_cmd(t_process *process, char **env);
void		px_validate_input(int argc, char **argv);
#endif