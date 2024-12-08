/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:17:30 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/08 03:08:17 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	manage_child(int argc, char **argv, int limit, int pipefd[2])
{
	char	**command;

	launch_pipe_series(argc, argv, limit - 1);
	command = get_command(argc, argv, limit);
	if (limit == argc - 2)
		command_executor(command);
	else
		pipe_command_executor(command, pipefd);
	free(command);
	return (1);
}

int	manage_parent(int pipefd[2], int pid)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(pid, 0, 0);
}

int	launch_pipe_series(int argc, char **argv, int limit)
{
	int		pid;
	int		pipefd[2];

	if (limit == 1)
		return (0);
	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
		manage_child(argc, argv, limit, pipefd);
	else if (pid > 0)
		manage_parent(pipefd, pid);
}

int	main(int argc, char **argv)
{
	int		fd_out;
	int		fd_in;

	if (argc < 5)
		return (ft_printf("Usage error"), 1);
	// if (!verify_command(argc, argv))
	// 	return (1);
	fd_in = open(argv[1], O_RDONLY);
	dup2(fd_in, STDIN_FILENO);
	fd_out = open(argv[argc - 1], O_CREAT | O_RDWR);
	dup2(fd_out, STDOUT_FILENO);
	launch_pipe_series(argc, argv, argc - 2);
	return (0);
}
