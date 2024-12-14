/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_set_input_output.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:42:36 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/14 16:40:08 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_here_doc(char *file)
{
	if (ft_strncmp(file, "here_doc", ft_strlen("here_doc") + 1) == 0)
		return (1);
	return (0);
}

int	build_here_doc(t_str *str, char *delimiter)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0)
	{
		if (!ft_str_push(str, line, ft_strlen(line)))
			return (0);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	get_next_line(~STDIN_FILENO);
	return (1);
}

int	set_here_doc(char *delimiter)
{
	t_str	*str;
	char	*buff;
	int		tmp_file;

	str = ft_str_create();
	if (!str)
		return (0);
	if (!build_here_doc(str, delimiter))
		return (ft_str_free(str), 0);
	buff = ft_str_get_char_array(str, str->size - str->start);
	if (!buff)
		return (0);
	tmp_file = open(delimiter, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	write(tmp_file, buff, str->size - str->start);
	return (close(tmp_file), free(buff), ft_str_free(str), 1);
}

int	set_input(char ***argv, int *argc)
{
	int	fd_in;
	int	status_here_doc;

	status_here_doc = 1;
	if (is_here_doc((*argv)[1]))
	{
		if (!set_here_doc((*argv)[2]))
			return (0);
		status_here_doc = 2;
		*argv = &(*argv)[1];
		(*argc)--;
	}
	fd_in = open((*argv)[1], O_RDONLY);
	if (fd_in == -1)
	{
		perror((*argv)[1]);
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
			return (perror("Failed to open /dev/null"), 0);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	if (status_here_doc == 2)
		unlink((*argv)[1]);
	return (status_here_doc);
}

int	set_ouput(int argc, char **argv)
{
	int		fd_out;

	fd_out = open(argv[argc - 1],
			O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd_out == -1)
	{
		perror(argv[argc - 1]);
		return (0);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (1);
}
