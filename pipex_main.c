/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:17:30 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/16 19:50:36 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_child(char **argv, int limit)
{
	char	**command;
	char	*command_buffer;

	command = ft_split(argv[limit], ' ');
	if (!command)
		return (ft_putstr_fd("Split failed in execute_child\n", 2), 0);
	command_buffer = command[0];
	command[0] = pathed_command(command[0]);
	if (!command[0])
	{
		ft_free_split(command);
		return (ft_putstr_fd("Command is null in execute_child\n", 2), 0);
	}
	if (command[0] != command_buffer)
		free(command_buffer);
	if (execve(command[0], command, environ) == -1)
	{
		perror(command[0]);
		ft_free_split(command);
		return (0);
	}
	return (1);
}

int	manage_child(int pipefd[2], int redirect)
{
	if (redirect && dup2(pipefd[1], STDOUT_FILENO) == -1)
		return (0);
	if (close(pipefd[0]) == -1)
		return (0);
	if (close(pipefd[1]) == -1)
		return (0);
	return (1);
}

int	manage_parent(int pipefd[2])
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		return (0);
	if (close(pipefd[1]) == -1)
		return (0);
	if (close(pipefd[0]) == -1)
		return (0);
	return (1);
}

int	launch_pipe_series(int argc, char **argv, int limit)
{
	int		pid;
	int		pipefd[2];
	int		stat_loc;

	if (limit == 1)
		return (1);
	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), 0);
	else if (pid == 0)
	{
		if (!manage_child(pipefd, limit != argc - 2))
			exit(1);
		launch_pipe_series(argc, argv, limit - 1);
		if (!execute_child(argv, limit))
			exit(1);
		exit(0);
	}
	else if (pid > 0)
		if (!manage_parent(pipefd) || wait(&stat_loc) == -1)
			return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int	status_here_doc;

	if (argc < 5)
		return (ft_putstr_fd("Usage error", 2), 1);
	status_here_doc = set_input(&argv, &argc);
	if (!status_here_doc)
		return (ft_putstr_fd("Input error", 2), 1);
	if (!set_ouput(argc, argv, status_here_doc))
		return (ft_putstr_fd("Output error", 2), 1);
	launch_pipe_series(argc, argv, argc - 2);
	return (0);
}
