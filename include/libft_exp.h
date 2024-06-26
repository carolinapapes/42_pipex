/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_exp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:37:08 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/21 00:04:11 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_EXP_H

# define LIBFT_EXP_H
# include "../include/px_types.h"

char const	*ft_str__find(char **env, char *key);
void		ft_split__free(char **strs);
char		*is_path(t_cmd *cmd);
char		*who(const char *str);
void		ft_free(void *content);

#endif