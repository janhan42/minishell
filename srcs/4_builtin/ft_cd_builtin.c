/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 09:43:03 by janhan            #+#    #+#             */
/*   Updated: 2024/03/21 22:47:23 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ft_cd_builtin(t_info *info, t_exec_info *exec_info)
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
			ft_printf_err("cd: %s: ", path);
			return (ft_perror(SUCCESS));
		}
		else
			exit(EXIT_SUCCESS);
	}
	// $PWD, $OLDPWD 바꾸는 부분
	// $PWD 는 지금 psth 넣어주면 될 것 같고
	// $OLDPWD 는 $PWD에 있던거 넣어주면 될듯
	// 그러려면 mini_ev 리스트 여기까지 가져와야함;;;;;;;;;
	
	// ft_change_path("OLDPWD", "PWD");
	// ft_change_path("PWD", path);
	//
	if (exec_info->builtin_parent == TRUE)
		return (SUCCESS);
	else
		exit(EXIT_SUCCESS);
}
