/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:07:42 by janhan            #+#    #+#             */
/*   Updated: 2024/03/13 10:28:36 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/_types/_pid_t.h>
# include <sys/_types/_size_t.h>
# include <sys/termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE -1
# define CHILD_PID 0
# define IN 0
# define OUT 1
# define NONE -1

#endif
