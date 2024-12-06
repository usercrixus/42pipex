/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:17:30 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/06 19:07:54 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/ft_printf/ft_printf.h"
#include "./libft/ft_base/libft.h"
#include "./libft/ft_str/ft_str.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

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
		waitpid(pid, NULL, 0);
	return (1);
}

int main(int argc, char **argv)
{
	char	*buffer;
	char	*command1;
	char	*command2;
	int		fd_in;
	int		fd_out;

	// command :
	buffer = ft_strtrim(argv[2], " ");
	command1 = ft_strjoin("/bin/", buffer);
	free(buffer);

	buffer = ft_strtrim(argv[3], " ");
	command2 = ft_strjoin("/bin/", buffer);
	free(buffer);

	fd_out = open(argv[4], O_CREAT | O_RDWR);
	dup2(fd_out ,STDOUT_FILENO);
	fd_in = open(argv[1], O_RDONLY);
	dup2(fd_in ,STDIN_FILENO);
	command_management(ft_split(command2, ' '));
	command_management(ft_split(command1, ' '));

	return (0);
}