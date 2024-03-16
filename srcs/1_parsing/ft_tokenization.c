/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:25:46 by janhan            #+#    #+#             */
/*   Updated: 2024/03/16 16:24:10 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_operator_process(t_parse *parse)
{
	char	redirect_c; // 리다이렉션 체크용

	if (parse->line[parse->line_index] == '|') // 파이프면
	{
		if (ft_make_token(parse, PIPE) == FAILURE) // 토큰을 만들어 type = PIPE
			return (FAILURE);
	}
	else if (ft_is_redirect(parse->line[parse->line_index])) // 리다이렉션이면
	{
		redirect_c = parse->line[parse->line_index]; // 오리지널 기호 저장하고
		if (parse->line[parse->line_index + 1] == redirect_c) // 앞에가 ex: >> 면
			parse->line_index++; // 하나 더 가
		if (ft_make_token(parse, REDIRECT) == FAILURE) // 만들어 type = REDIRECT
			return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief
 * 그냥 end_quote 넘어가기.
 * @param parse
 */
static void	ft_quote_process(t_parse *parse)
{
	char	end_quote;

	end_quote = parse->line[parse->line_index]; // 저장후
	parse->line_index++; // 한칸 ++
	while (parse->line[parse->line_index] // 끝까지
		&& parse->line[parse->line_index] != end_quote)
		parse->line_index++;
}

static int	ft_character_process(t_parse *parse)
{
	while (parse->line[parse->line_index])
	{
		if (ft_is_quote(parse->line[parse->line_index]) == TRUE) // " ' 두개 사실상 안에있는 것들은 명령어여도 단어취급이니까
			ft_quote_process(parse);
		if (parse->line[parse->line_index + 1] == '\0' // 널이거나
			|| ft_is_space(parse->line[parse->line_index + 1]) == TRUE // 공백 이거나
			|| ft_is_operator(parse->line[parse->line_index + 1]) == TRUE) // 오퍼레이터면
		{
			if (ft_make_token(parse, WORD) == FAILURE) //만들고
				return (FAILURE);
			return (SUCCESS); // 리턴
		}
		parse->line_index++;
	}
	return (SUCCESS);
}

int	ft_tokenization(t_parse *parse)
{
	while (parse->line[parse->line_index])
	{
		if (ft_is_space(parse->line[parse->line_index]) == TRUE) //다시 공백 띄어넘어
			;
		else if (ft_is_operator(parse->line[parse->line_index]) == TRUE) // 오퍼레이터 체크
		{
			if (ft_operator_process(parse) == FAILURE)
				return (FAILURE);
		}
		else // cat "Hello" 이런 명령어 단어? 그런거 오퍼레이터가 아닌애들
		{
			if (ft_character_process(parse) == FAILURE)
				return (FAILURE);
		}
		parse->line_index++; // 진행 인덱스
		parse->start_index = parse->line_index; // 처음 시작 인덱스
	}
	return (SUCCESS);
}
