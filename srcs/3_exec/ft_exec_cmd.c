/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:01:16 by janhan            #+#    #+#             */
/*   Updated: 2024/03/19 13:04:50 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>
#include <stdlib.h>

void	ft_exec_cmd(t_info *info, t_parse *parse,
	t_exec *exec, t_exec_info *exec_info)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (ft_is_builtin(exec_info) == FALSE
		&& ft_find_cmd(exec, exec_info) == FAILURE)
	{
		ft_printf_err("%s: command not found\n", exec_info->cmd[0]);
		ft_free_all(parse, exec);
		exit(127);
	}
	else
	{
		ft_set_fd(exec, exec_info);
		if (exec_info->cmd_path == NULL)
			exit(EXIT_SUCCESS);
		if (ft_is_builtin(exec_info) == TRUE)
			ft_exec_builtin(info, parse, exec, exec_info);
		else
			execve(exec_info->cmd_path, exec_info->cmd,)
	}
}
