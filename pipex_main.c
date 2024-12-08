/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:17:30 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/08 04:22:53 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	manage_child(int argc, char **argv, int limit, int pipefd[2])
{
	char	**command;

	command = get_command(argc, argv, limit);
	if (limit == argc - 2)
	{
		command_executor(command);
	}
	else
	{
		pipe_command_executor(command, pipefd);
	}
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

	if (limit == 2)
		return (0);
	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		launch_pipe_series(argc, argv, --limit);
		manage_child(argc, argv, limit, pipefd);
	}
	else if (pid > 0)
		manage_parent(pipefd, pid);
}

int	set_input(char **argv)
{
	int		fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		perror(argv[1]);
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
		{
			perror("Failed to open /dev/null");
			return (0);
		}
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return(1);
}

int	set_ouput(int argc, char **argv)
{
	int		fd_out;

	fd_out = open(argv[argc - 1], O_CREAT | O_RDWR);
	if (fd_out == -1)
	{
		perror(argv[argc - 1]);
		return(0);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return(1);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
		return (ft_printf("Usage error"), 1);
	// if (!verify_command(argc, argv))
	// 	return (1);
	if(!set_input(argv))
		return(1);
	if (!set_ouput(argc, argv))
		return(1);
	launch_pipe_series(argc, argv, argc - 1);
	return (0);
}
