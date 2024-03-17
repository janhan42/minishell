/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 09:48:52 by janhan            #+#    #+#             */
/*   Updated: 2024/03/17 09:54:06 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stddef.h>
#include <stdlib.h>

static char **ft_echo_builtin_malloc_str(t_exec_info *exec_info)
{
	char	**str;
	size_t	str_size;

	str_size = 1;
	while (exec_info->cmd[str_size])
		str_size++;
	str = (char **)ft_calloc(str_size, sizeof(char *));
	if (str == NULL)
		exit(EXIT_FAILURE);
	return (str);
}

int ft_cd_builtin(t_exec_info *exec_info)
{
	char	**str;
	size_t	str_i;
	size_t	cmd_i;
	int		n_flag;

	if (exec_info->cmd[1] == NULL)
	{
		printf("\n");
		exit(SUCCESS);
	}
	str = ft_echo_builtin_malloc_str(exec_info);
	n_flag = FALSE;
	str_i = 0;
	cmd_i = ft_echo_builtin_find_cmd_i(exec_info->cmd, &n_flag);
}
