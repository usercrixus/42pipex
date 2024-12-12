/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:17:30 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/12 17:22:19 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	manage_child(int argc, char **argv, int limit, int pipefd[2])
{
	char	**command;

	command = get_command(argc, argv, limit);
	command[0] = verify_command(command[0]);
	if (!command[0])
	{
		ft_putstr_fd("Command ", 2);
		ft_putstr_fd(argv[limit], 2);
		ft_putstr_fd(": not found.\n", 2);
		return (0);
	}
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
	status = waitpid(pid, 0, 0);
	if (status == -1)
		return (0);
	return (1);
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
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int	intput_status;

	if (argc < 5)
		return (ft_printf("Usage error"), 1);
	if (!set_input(&argv, &argc))
		return (1);
	if (!set_ouput(argc, argv))
		return (1);
	launch_pipe_series(argc, argv, argc - 1);

	return (0);
}
