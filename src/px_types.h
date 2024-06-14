/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:15:47 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/13 22:46:56 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_TYPES_H
# define PX_TYPES_H

# define PROG_NAME "pipex"

# define READ_END 0
# define WRITE_END 1

# define FT_FD_INIT 1
# define FT_FD_ERROR 2
# define FT_FD_DUP 4
# define FT_FD_CLOSE 8

# define PROG_NAME "pipex"

typedef struct s_process
{
	int			pid;
	int			input[2];
	int			output[2];
}	t_process;

typedef struct s_program
{
	char		*fd_names[2];
	int			cmdc;
	char		**cmdv;
	char		**env;
}				t_program;

typedef struct s_cmd
{
	char	*str;
	char	**arr;
	char	**env;
	char	*path;
}	t_cmd;

#endif