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

char const	*ft_str__find(char **env, char *key);
void		ft_split__free(char **strs);
void		is_dir(char *name);
char		*is_path(char *name, char **path);
char		*who(const char *str);
void		ft_free(void *content);

#endif