/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:05:11 by janhan            #+#    #+#             */
/*   Updated: 2024/03/16 16:24:37 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <inttypes.h>

static int	ft_pipe_process(t_parse *parse)
{
	if (parse->line[parse->line_index + 1] == '|') // "||" 미지원처리
	{
		g_child_exit_code = 258;
		return (ft_error("Syntax Error: Not support '||' symbol in minishell" // 응 안되
			, FAILURE));
	}
	else // 그게 아니면 토큰 개수 ++
		parse->token_count++;
	return (SUCCESS);
}

static int	ft_redirect_process(t_parse *parse)
{
	char	redirect_c;
	int		repeat_count;

	repeat_count = 1; // > 하나 감지하고 들어왔으니까 1로 시작
	redirect_c = parse->line[parse->line_index]; // >< 이거 방지용
	while (parse->line[parse->line_index + 1] == redirect_c) // 만약에 > 저장한거랑 같으면
	{
		repeat_count++; // 반복 >> 증가
		if (repeat_count == 3) // 3 개면 미지원 처리
		{
			g_child_exit_code = 258;
			return (ft_error("Syntax Error: Used \
			more than 3 redirecting character (Ex: '<<<...')", FAILURE));
		}
		parse->line_index++;
	}
	parse->token_count++; // 토큰 갯수 카운트
	return (SUCCESS);
}

static int	ft_operator_process(t_parse *parse) // 오퍼레이터 갈라치기
{
	if (parse->line[parse->line_index] == '|') // 파이프면
	{
		if (ft_pipe_process(parse) == FAILURE)
			return (FAILURE);
	}
	else if (ft_is_redirect(parse->line[parse->line_index]) == TRUE) // 리다이렉션이면
		if (ft_redirect_process(parse) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

/*
Not interpret unclosed quotes or unspecified special characters like \ (backslash) or ; (semicolon).
닫히지 않은 따옴표나 특정되지 않은 특수문자 (\나 ; 등...) 을 해석하지 않아야 합니다.
*/
static int	ft_quote_process(t_parse *parse)
{
	char	end_quote;

	end_quote = parse->line[parse->line_index]; // 처음 들어온거 감지하고 왔으니 " " 짝이 맞아야함
	parse->line_index++; // 한칸 넘겨
	while (parse->line[parse->line_index]
		&& parse->line[parse->line_index] != end_quote) // \0이던지 end_quote랑 같던지.
		parse->line_index++;
	if (parse->line[parse->line_index] == '\0') // 근데 짝없이 널이면 에러처리
	{
		g_child_exit_code = 258;
		// ft_printf_err("Systax Error: Quote %c is not closed\n", end_quote); // end_quote 짝이 안맞음
		printf("Systax Error: Quote %c is not closed\n", end_quote); // end_quote 짝이 안맞음
		return (FAILURE);
	}
	return (SUCCESS);
}
/**
 * @brief
 * parse->line = 전체 명령어
 ->
 * @param parse
 * @return int
 */
int	ft_count_token(t_parse *parse)
{
	while (parse->line[parse->line_index])
	{
		if (ft_is_space(parse->line[parse->line_index]) == TRUE)
			;
		else if (ft_is_operator(parse->line[parse->line_index]) == TRUE) // 오퍼레이터 | > >> < <<
		{
			if (ft_operator_process(parse) == FAILURE)
				return (FAILURE);
		}
		else // 그것이 아니면
		{
			if (ft_is_quote(parse->line[parse->line_index]) == TRUE) // ' " 봐
				if (ft_quote_process(parse) == FAILURE)
					return (FAILURE);
			if (parse->line[parse->line_index + 1] == '\0' // (앞에 공백 날렸음)cat
				|| ft_is_space(parse->line[parse->line_index + 1]) == TRUE
				|| ft_is_operator(parse->line[parse->line_index + 1]) == TRUE)
				parse->token_count++;
		}
		parse->line_index++;
	}
	return (SUCCESS);
}
