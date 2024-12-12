/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:33:22 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/12 17:06:37 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path()
{
	int		i;
	char	*line;
	char	**paths;

	i = 0;
	line = environ[i];
	while (ft_strncmp("PATH=", line, ft_strlen("PATH=")) != 0)
	{
		i++;
		line = environ[i];
	}
	if (ft_strncmp("PATH=", line, ft_strlen("PATH=")) != 0)
		return (0);
	line += ft_strlen("PATH=");
	paths = ft_split(line, ':');
	if (!paths)
		return (0);
	return (paths);
}

char	*verify_command(char *command)
{
	int		fd;
	int		status;
	char	*command_pathed;
	char	*path;
	char	**paths;
	int		i;

	paths = get_path();
	if (!paths)
		return (0);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		command_pathed = ft_strjoin(path, command);
		free(path);
		if (access(command_pathed, F_OK) == 0)
			return (ft_free_split(paths), command_pathed);
		i++;
	}
	return (ft_free_split(paths), (char *)0);
}

char	**get_command(int argc, char **argv, int i)
{
	char	**command_array;

	command_array = ft_split(argv[i], ' ');
	return (command_array);
}
