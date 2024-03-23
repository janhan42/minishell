/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:00:03 by janhan            #+#    #+#             */
/*   Updated: 2024/03/22 14:49:02 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node	*ft_find_node(char *to_find2, t_list *list)
{
	t_node	*cur;
	size_t	to_find_len;
	char	**temp;
	char	*to_find;

	temp = ft_split(to_find2, '=');
	to_find = temp[0];
	free(temp[1]);
	free(temp);
	cur = list->front_node;
	to_find_len = ft_strlen(to_find);
	while (cur)
	{
		if ((ft_strncmp(to_find, cur->content, to_find_len + 1) == 0)
			|| (ft_strncmp(to_find, cur->content, to_find_len + 1) == -61))
		{
			free(to_find);
			return (cur);
		}
		cur = cur->next_node;
	}
	free(to_find);
	return (NULL);
}

static int	ft_unset_builtin_arg_check(char *str)
{
	size_t	i;

	i = 0;
	// unset '' -> 고치는 중
	if (str[0] == '\0') // 첫글자가 널이면 뒤에 코드 실행되면 안됨
		return (FAILURE);
	// 추가부분 끝
	if (ft_isalpha(str[0]) == FALSE && str[0] != '_')
		return (SUCCESS);
	while (str[i])
	{
		if (str[i] == '=')
			return (FAILURE);
		if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static void	ft_unset_builtin_del_node(t_info *info, t_exec_info *exec_info)
{
	size_t	i;
	t_node	*to_delete;

	i = 1;
	while (exec_info->cmd[i])
	{
		if (ft_unset_builtin_arg_check(exec_info->cmd[i]) == FAILURE)
		{
			ft_printf_err("unset: '%s': not a vaild identifier\n",
				exec_info->cmd[i++]);
			continue ;
		}
		to_delete = ft_find_node(exec_info->cmd[i], &(info->mini_ev));
		if (to_delete)
			ft_list_del_node(&(info->mini_ev), to_delete);
		i++;
	}
}

int	ft_unset_builtin(t_info *info, t_exec_info *exec_info)
{
	if (exec_info->cmd[1] == NULL)
	{
		if (exec_info->builtin_parent == TRUE)
			return (SUCCESS);
		else
			exit(SUCCESS);
	}
	else
		ft_unset_builtin_del_node(info, exec_info);
	if (exec_info->builtin_parent == TRUE)
		return (SUCCESS);
	else
		exit(SUCCESS);
}
