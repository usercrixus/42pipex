/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:33:22 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/12 19:37:24 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(void)
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
		if (!path)
			return (0);
		command_pathed = ft_strjoin(path, command);
		if (!command_pathed)
			return (0);
		free(path);
		if (access(command_pathed, F_OK) == 0)
			return (ft_free_split(paths), command_pathed);
		free(command_pathed);
		i++;
	}
	return (ft_free_split(paths), (char *)0);
}