/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:21:42 by janhan            #+#    #+#             */
/*   Updated: 2024/03/16 17:46:12 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief
 * 가장 최근의 자식프로세스의 종료코드를 현재 토큰에 저장
 * @param parse
 * @return int
 */
int	ft_convert_child_exit_code(t_parse *parse)
{
	parse->exit_code = ft_itoa(g_child_exit_code); // exit코드를 문자열로 parse->exit_code 문자열로 저장
	if (parse->exit_code == NULL)
		return (FAILURE);
	parse->token->str[parse->str_index] = '\0'; // strjoin 덮어쓰기 용 [$][?] -> [\0][\n]
	parse->old_str = ft_strjoin(parse->token->str, parse->exit_code); // strjoin으로 덮어씀
	if (parse->old_str == NULL)
	{
		free(parse->exit_code);
		return (FAILURE);
	}
	parse->new_str
		= ft_strjoin(parse->old_str, &parse->token->str[parse->str_index + 2]);
	if (parse->new_str == NULL)
	{
		free(parse->exit_code);
		free(parse->old_str);
		return (FAILURE);
	}
	free(parse->token->str); // 기존 거 프리
	parse->token->str = parse->new_str; // 새로 연결
	parse->str_index += ft_strlen(parse->exit_code) - 1; // exit_code 길이의 -1
	free(parse->exit_code); // 할당 프리
	free(parse->old_str); // 할당 프리
	return (SUCCESS);
}
