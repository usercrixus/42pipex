/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:33:22 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/07 22:07:36 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	verify_command(int argc, char ** argv)
{
	int		fd;
	int		status;
	char	*command_pathed;

	status = 1;
	while (argc - 2 > 1)
	{
		command_pathed = ft_strjoin(PATH, argv[argc - 2]);
		fd = open(command_pathed, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("%s: command not found\n", argv[argc - 2]);
			status = 0;
		}
		free(command_pathed);
		argc--;
	}
	return (status);
}

char	*get_command(int argc, char **argv, int i)
{
	return (ft_strjoin(PATH, argv[argc - 2 - i]));
}

int	get_file()
{

}