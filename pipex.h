/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinapapes <carolinapapes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:37:37 by carolinapap       #+#    #+#             */
/*   Updated: 2024/06/05 15:56:45 by carolinapap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

#define PIPEX_H

#define READ_END 0
#define WRITE_END 1

typedef struct s_pipe
{
	int	fd[2];
	int	pid;
	int	pid_2;
	int	pid_signal[1];
	int	pid_2_signal[1];
	int	inout_fd[2];
}		t_pipe;

typedef struct s_cmd
{
	char	*env_path;
	char	**args;
}		t_cmd;

int	is_parse_valid(int argc, char **argv);
int	pipex(int argc, char **argv, char **envp);
int	command_exec(char *command, char **envp);

#endif