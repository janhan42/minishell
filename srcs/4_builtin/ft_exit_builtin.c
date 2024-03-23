/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:03:27 by janhan            #+#    #+#             */
/*   Updated: 2024/03/23 00:57:17 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_isnum(int c)
{
	if ('0' <= c && c <= '9')
		return (TRUE);
	else
		return (FALSE);
}

static void	ft_exit_builtin_arg_check(t_exec *exec, size_t i, int sing_flag)
{
	exec->exec_arr[exec->exec_arr_index].cmd[1]
		= ft_strtrim(exec->exec_arr[exec->exec_arr_index].cmd[1], " ");
	while (exec->exec_arr[exec->exec_arr_index].cmd[1][i])
	{
		if (ft_isnum(exec->exec_arr[exec->exec_arr_index].cmd[1][i]))
			i++;
		else
		{
			printf("exit\nexit: %s: numeric argument reauired\n",
				exec->exec_arr[exec->exec_arr_index].cmd[1]);
			exit(255);
		}
	}
	if (i == 1 && sing_flag == TRUE)
	{
		printf("exit\nexit: %s: numeric argument required\n",
			exec->exec_arr[exec->exec_arr_index].cmd[1]);
		exit(255);
	}
}

static void	ft_exit_builtin_isnum(t_exec *exec)
{
	size_t	i;
	int		sign_flag;

	sign_flag = FALSE;
	i = 0;
	if ((exec->exec_arr[exec->exec_arr_index].cmd[1][0] == '-')
		|| (exec->exec_arr[exec->exec_arr_index].cmd[1][0] == '+'))
	{
		sign_flag = TRUE;
		i++;
	}
	ft_exit_builtin_arg_check(exec, i, sign_flag);
	printf("exit\n");
}

static void	ft_exit_builtin_no_arg(t_list *mini_ev, t_parse *parse,
	t_exec *exec, t_exec_info *exec_info)
{
	if ((exec->exec_arr[exec->exec_arr_index].cmd[1]) == NULL)
	{
		if (exec_info->builtin_parent == FALSE)
			printf("exit\n");
		ft_list_clear(mini_ev);
		ft_free_all(parse, exec);
		exit(EXIT_SUCCESS);
	}
}

int	ft_exit_builtin(t_list *mini_ev, t_parse *parse, t_exec *exec,
	t_exec_info *exec_info)
{
	int	exit_value;

	ft_exit_builtin_no_arg(mini_ev, parse, exec, exec_info);
	if (exec->exec_arr[exec->exec_arr_index].cmd[2])
	{
		printf("exit\nminishell: exit: too many arguments\n");
		g_child_exit_code = 1;
		if (exec_info->builtin_parent == TRUE)
			return (SUCCESS);
		else
			exit(1);
	}
	ft_exit_builtin_isnum(exec);
	exit_value = ft_atoi(exec->exec_arr[exec->exec_arr_index].cmd[1]);
	ft_list_clear(mini_ev);
	ft_free_all(parse, exec);
	exit(exit_value);
}

/*
	exit ‘  3 ‘ 식으로 공백 들어가는건 에러 안나와야 하는거
	bash 테스트상 exit ' 34'가능
				exit '3 4' 불가능
				exit ' 3a' 불가능 이니까 좌우 trim 함수만들어서 사용 하면 될듯
*/
