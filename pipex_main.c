/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:17:30 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/07 22:06:09 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int command_executor(char **command)
{
    if (execve(command[0], command, 0) == -1)
        return (1);
    return (0);
}

int	command_management(char **command)
{
	int pid;

	pid = fork();
    if (pid == -1)
		return (0);
	if (pid == 0)
	    command_executor(command);
	else if (pid > 0)
		wait(NULL);
	return (1);
}

int	launch_all_command(int argc, char **argv)
{
	char	*command;
	char	**command_array;
	int		i;
	int		fd_in;
	int		std_in;
	int		std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	i = 0;
	while (i < argc - 2)
	{
		if (i == argc - 4)
		{
			fd_in = open(argv[1], O_RDONLY);
			dup2(fd_in ,STDIN_FILENO);

		}

		command = get_command(argc, argv, i);
		command_array = ft_split(command, ' ');
		command_management(command_array);
		free(command_array);
		i++;
	}
}

int main(int argc, char **argv)
{
	int		fd_out;


	if (argc < 5)
		return (ft_printf("Usage error"), 1);
	if (!verify_command(argc, argv))
		return (1);
	//launch_all_command(argc, argv);

	// fd_out = open(argv[4], O_CREAT | O_RDWR);
	// dup2(fd_out ,STDOUT_FILENO);

	return (0);
}