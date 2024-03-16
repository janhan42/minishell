/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:59:19 by janhan            #+#    #+#             */
/*   Updated: 2024/03/16 18:07:50 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>

/**
 * @brief
 * 따음표 플래그 처리
 * @param parse
 */

static void	ft_set_quote_flag(t_parse *parse)
{
	if (parse->token->str[parse->str_index] == '"' // 만약에 (") 나왔어
		&& parse->dquote_flag == FALSE) // 근데 더블 쿼트가 FALSE면
		parse->dquote_flag = TRUE; // TRUE 바꿔
	else if (parse->token->str[parse->str_index] == '"'
		&& parse->dquote_flag == TRUE)
		parse->dquote_flag = FALSE;
	if (parse->token->str[parse->str_index] == '\''
		&& parse->dquote_flag == FALSE
		&& parse->squote_flag == FALSE)
		parse->squote_flag = TRUE;
	else if (parse->token->str[parse->str_index] == '\''
		&& parse->dquote_flag == FALSE
		&& parse->squote_flag == TRUE)
		parse->squote_flag = FALSE;
}
// $AAA="1234";
//  ^ ^
// AAA=
// 환경변수 노드가 만들어졌다.
static int	ft_check_env(t_info *info, t_parse *parse)
{
	parse->start_index = parse->str_index; // 시작인덱스는 str인덱스
	while (ft_isalnum(parse->token->str[parse->str_index + 1]) // 부호다음에 숫자 혹은 문자
		|| parse->token->str[parse->str_index + 1] == '-'
		|| parse->token->str[parse->str_index + 1] == '+')
		parse->str_index++; // 인덱스 ++
	parse->temp_str_len = parse->str_index - parse->start_index; // 저장할 문자의 길이
	parse->temp_str = (char *)ft_calloc(parse->temp_str_len, sizeof(char)); // calloc
	if (parse->temp_str == NULL)
		return (ft_error("Failed calloc temp_str", FAILURE));
	ft_strlcpy(parse->temp_str, &parse->token->str[parse->start_index + 1],
		parse->temp_str_len + 1); // strlcpy로 저장
	parse->target_ev = ft_strjoin(parse->temp_str, "="); // =표시문자열에 저장
	if (parse->target_ev == NULL)
	{
		free(parse->temp_str);
		return (ft_error("Failed ft_strjoin target_eb", FAILURE));
	}
	free(parse->temp_str); // temp free;
	if (ft_is_env(info, parse) == TRUE)
		return (TRUE);
	free(parse->target_ev);
	return (FALSE);
}
// ( AAA=\0)
//       ^
// start=0;

// 떠온 뒷부분을

static int	ft_add_env(t_parse *parse)
{
	parse->token->str[parse->start_index] = '\0';
	parse->old_str = ft_strjoin(parse->token->str, parse->ev_val);
	if (parse->old_str == NULL)
	{
		free(parse->target_ev);
		free(parse->ev_val);
		return (ft_error("Failed ft_strjoin old_str", FAILURE));
	}
	parse->new_str
		= ft_strjoin(parse->old_str, &parse->token->str[parse->token_index + 1]);
	if (parse->new_str == NULL)
	{
		free(parse->target_ev);
		free(parse->ev_val);
		free(parse->old_str);
		return (ft_error("Failed ft_strjoin new_str", FAILURE));
	}
	free(parse->target_ev); // 위에서 만든 이름 프리
	free(parse->ev_val); // ft_is_env에서 만든 변수 프리
	free(parse->old_str); // 프리
	free(parse->token->str); // 기존 토큰이 가지고있던 문자열 프리
	parse->token->str = parse->new_str; // -> new_str = "AAA=변수값" 이상태로 저장.
										// 기존토큰 = "$AAA=변수값" -> 
	return (SUCCESS);
}

static int	ft_find_env(t_info *info, t_parse *parse)
{
	ft_set_quote_flag(parse);
	if (parse->squote_flag == FALSE && parse->token->str[parse->str_index] == '$'
		&& (ft_isalpha(parse->token->str[parse->str_index + 1])
			|| parse->token->str[parse->str_index + 1] == '_'
			|| parse->token->str[parse->str_index + 1] == '+'
			|| parse->token->str[parse->str_index + 1] == '?'))
	{
		if (ft_is_child_exit_code(parse) == TRUE) // ? 처리
			return (ft_convert_child_exit_code(parse));
		else if (ft_check_env(info, parse) == TRUE) // 부호 처리면
		{
			if (ft_add_env(parse) == FAILURE)
				return (FAILURE);
			parse->str_index = parse->start_index + parse->ev_val_len - 1;
		}
		else
		{
			ft_strlcpy(&parse->token->str[parse->start_index],
				&parse->token->str[parse->str_index + 1],
				ft_strlen(parse->token->str) + 1);
			parse->str_index -= parse->temp_str_len + 1;
		}
	}
	return (SUCCESS);
}
/**
 * @brief
 * 토큰 다짤랐음 이제 토큰을 돌면서 체크해야해
 * @param info
 * @param parse
 * @return int
 */
 // (cat) (<<)(skip) (히어독 검별자)
int	ft_convert_env(t_info *info, t_parse *parse)
{
	parse->token_index = 0; // 우리가 ++하면서 만들었던 index를 다시 0으로
	while (parse->token_index < parse->token_count) // 토큰 개수만큼
	{
		parse->token = &parse->tokens[parse->token_index]; // 현재 토큰 저장
		parse->str_index = 0; // str의 인덱스 0 -> 자른 명령어 검사?
		while (parse->token->str[parse->str_index]) // 한글자씩
		{
			if (ft_is_heredoc(parse->token->str[parse->str_index], // 자른부분의 앞부분이 히어독 표시면 (<< = heredoc)
				parse->token->str[parse->str_index + 1]) == TRUE)
			{
				parse->token_index++; // 넘어가
				break ; // 반복문 탈출 히어독은 실행부에서 관리해야해
			}
			if (ft_find_env(info, parse) == FAILURE) // 그게아니면
				return (FAILURE);
			parse->str_index++;
		}
		parse->token_index++;
	}
	return (SUCCESS);
}
