/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:25:46 by janhan            #+#    #+#             */
/*   Updated: 2024/03/02 15:23:07 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/_types/_pid_t.h>

static int	ft_wait_child(t_exec *exec)
{
	int		child_status;
	pid_t	last_child_pid;

	last_child_pid = exec->exec_arr[exec->exec_arr_size - 1].pid;
	exec->exec_arr_index = 0;
	while (exec->exec_arr_index < exec->exec_arr_size)
	{
		exec->current_child_pid = waitpid(-1, )
	}
}

static int	ft_here_doc(t_parse *parse, t_exec *exec)
{
	if (ft_check_here_doc(exec) == FAILURE)
	{
		ft_free_all(parse, exec);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_exec(t_info *info, t_parse *parse, t_exec *exec)
{
	t_exec_info	*exec_info;

	if (ft_here_doc(parse, exec) == FAILURE)
		return (FAILURE);
	exec->exec_arr_index = 0;
	while (exec->exec_arr_index < exec->exec_arr_size)
	{
		exec_info = &exec->exec_arr[exec->exec_arr_index];
		if (ft_is_builtin_parent(exec, exec_info) == TRUE)
			return (ft_exec_builtin_parent(info, parse, exec, exec_info));
		if (exec_info->use_pipe == TRUE)
		{
			if (pipe(exec_info->pipe_fd) == FAILURE)
			{
				ft_free_all(parse, exec);
				return (ft_perror(FAILURE));
			}
			if (ft_make_child(info, parse, exec, exec_info) == FAILURE)
				return (FAILURE);
			exec->exec_arr_index++;
		}
		ft_wait_child(exec);
		return (SUCCESS);
	}
}
