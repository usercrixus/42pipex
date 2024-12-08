/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:32:58 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/08 02:50:50 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define PATH "/bin/"

# include <fcntl.h>
# include "libft/ft_printf/ft_printf.h"
# include "./libft/ft_base/libft.h"
# include "./libft/ft_str/ft_str.h"
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
int			verify_command(int argc, char **argv);
char		**get_command(int argc, char **argv, int i);

#endif