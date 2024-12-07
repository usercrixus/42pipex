/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:32:58 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/07 20:50:27 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/ft_printf/ft_printf.h"
#include "./libft/ft_base/libft.h"
#include "./libft/ft_str/ft_str.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef PIPEX_H
# define PIPEX_H
# define PATH "/bin/"

int		verify_command(int argc, char ** argv);
char	*get_command(int argc, char **argv, int i);

#endif