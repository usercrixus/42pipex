/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:32:58 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/15 04:30:50 by achaisne         ###   ########.fr       */
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
char		*pathed_command(char *command);
int			set_ouput(int argc, char **argv, int status_here_doc);
int			set_input(char ***argv, int *argc);

#endif