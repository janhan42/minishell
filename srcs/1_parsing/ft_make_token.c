/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:32:02 by janhan            #+#    #+#             */
/*   Updated: 2024/03/16 16:47:43 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief
 * 토큰 배열에 make
 * @param parse
 * @param type -> PIPE, WORD, REDIRECT
 * @return int 성공 여부
 */
int	ft_make_token(t_parse *parse, t_token_type type)
{
	parse->tokens[parse->token_index].type = type; // -> 들어온 type으로 구조체 정보 변경.
	parse->temp_str
		= (char *)ft_calloc(parse->line_index - parse->start_index + 2, sizeof(char)); // line_index - start_index + 1
	if (parse->temp_str == NULL)
		return (ft_error("Failed calloc temp_str", FAILURE));
	ft_strlcpy(parse->temp_str, &parse->line[parse->start_index], parse->line_index - parse->start_index + 2); // lcpy로 명령어 부분 복사.
	parse->tokens[parse->token_index].str = parse->temp_str; //token구조체에 str = str;
	parse->token_index++; // token_index++;
	return (SUCCESS);
}
