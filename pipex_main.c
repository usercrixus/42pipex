/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:17:30 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/13 03:49:17 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	manage_child(int argc, char **argv, int limit, int pipefd[2])
{
	char	**command;
	char	*command_buffer;

	command = ft_split(argv[limit], ' ');
	command_buffer = command[0];
	command[0] = pathed_command(command[0]);
	if (command[0] != command_buffer)
		free(command_buffer);
	if (limit == argc - 2 && !command_executor(command))
	{
		perror(command[0]);
		ft_free_split(command);
		exit(1);
	}
	else if (!pipe_command_executor(command, pipefd))
	{
		perror(command[0]);
		ft_free_split(command);
		exit(1);
	}
}

int	manage_parent(int pipefd[2])
{
	int	status;

	status = dup2(pipefd[0], STDIN_FILENO);
	if (status == -1)
		return (0);
	status = close(pipefd[1]);
	if (status == -1)
		return (0);
	status = close(pipefd[0]);
	if (status == -1)
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
		launch_pipe_series(argc, argv, limit - 1);
		manage_child(argc, argv, limit, pipefd);
	}
	else if (pid > 0)
	{
		if (!manage_parent(pipefd))
			return (0);
		if (wait(&stat_loc) == -1)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
		return (ft_putstr_fd("Usage error", 2), 1);
	if (!set_input(&argv, &argc))
		return (ft_putstr_fd("Input error", 2), 1);
	if (!set_ouput(argc, argv))
		return (ft_putstr_fd("Output error", 2), 1);
	launch_pipe_series(argc, argv, argc - 2);
	return (0);
}
