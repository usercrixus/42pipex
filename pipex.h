/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:32:58 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/12 16:57:30 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define PATH "/bin/"

# include "./libft/ft_printf/ft_printf.h"
# include "./libft/ft_base/libft.h"
# include "./libft/ft_str/ft_str.h"
# include "./libft/ft_gnl/ft_get_next_line.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

extern char	**environ;
int			command_executor(char **command);
int			pipe_command_executor(char **command, int pipefd[2]);
int			launch_pipe_series(int argc, char **argv, int limit);
char		*verify_command(char *command);
char		**get_command(int argc, char **argv, int i);
int			set_ouput(int argc, char **argv);
int			set_input(char ***argv, int *argc);

#endif