/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipe_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 00:39:03 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/09 20:14:01 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	command_executor(char **command)
{
	if (execve(command[0], command, environ) == -1)
	{
		perror(command[0]);
		return (0);
	}
	return (1);
}

int	pipe_command_executor(char **command, int pipefd[2])
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (execve(command[0], command, environ) == -1)
	{
		perror(command[0]);
		return (0);
	}
	return (1);
}
