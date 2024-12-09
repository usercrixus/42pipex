/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_set_input_output.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:42:36 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/09 20:15:44 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_here_doc(char *file)
{
	if (ft_strncmp(file, "here_doc", ft_strlen("here_doc")) == 0)
		return (1);
	return (0);
}

int	set_here_doc(char *delimiter)
{
	t_str	*str;
	char	*line;
	char	*buff;
	int		tmp_file;

	str = ft_str_create();
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			get_next_line(~STDIN_FILENO);
			break ;
		}
		ft_str_push(str, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	buff = ft_str_get_char_array(str, str->size - str->start);
	tmp_file = open(delimiter, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	write(tmp_file, buff, str->size - str->start);
	free(buff);
	ft_str_free(str);
	return (1);
}

int	set_input(char ***argv, int *argc)
{
	int	fd_in;
	int	intput_status;

	intput_status = 1;
	if (is_here_doc((*argv)[1]))
	{
		set_here_doc((*argv)[2]);
		intput_status = 2;
		*argv = &(*argv)[1];
		(*argc)--;
	}
	fd_in = open((*argv)[1], O_RDONLY);
	if (fd_in == -1)
	{
		perror((*argv)[1]);
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
		{
			perror("Failed to open /dev/null");
			return (0);
		}
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (intput_status);
}

int	set_ouput(int argc, char **argv)
{
	int		fd_out;

	fd_out = open(argv[argc - 1], O_CREAT | O_RDWR);
	if (fd_out == -1)
	{
		perror(argv[argc - 1]);
		return (0);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (1);
}
