/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 09:43:03 by janhan            #+#    #+#             */
/*   Updated: 2024/03/17 09:48:30 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ft_cd_builtin(t_exec_info *exec_info)
{
	char	*path;

	path = exec_info->cmd[1];
	if (path == NULL)
	{
		if (exec_info->builtin_parent == TRUE)
			return (SUCCESS);
		else
			exit(EXIT_SUCCESS);
	}
	if (chdir(path) == FAILURE)
	{
		g_child_exit_code = 1;
		if (exec_info->builtin_parent == TRUE)
		{
			ft_printf("cd: %s: ", path);
			return (ft_perror(SUCCESS));
		}
		else
			exit(EXIT_SUCCESS);
	}
	if (exec_info->builtin_parent == TRUE)
		return (SUCCESS);
	else
		exit(EXIT_SUCCESS);
}
