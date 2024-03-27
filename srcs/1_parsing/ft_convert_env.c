/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:59:19 by janhan            #+#    #+#             */
/*   Updated: 2024/03/27 15:20:18 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <sys/stat.h>

static void	ft_set_quote_flag(t_parse *parse)
{
	if (parse->token->str[parse->str_index] == '"'
		&& parse->dquote_flag == FALSE)
		parse->dquote_flag = TRUE;
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

static int	ft_check_env(t_info *info, t_parse *parse)
{
	parse->start_index = parse->str_index;
	while (ft_isalnum(parse->token->str[parse->str_index + 1])
		|| parse->token->str[parse->str_index + 1] == '-'
		|| parse->token->str[parse->str_index + 1] == '_')
		parse->str_index++;
	parse->temp_str_len = parse->str_index - parse->start_index + 1;
	parse->temp_str = (char *)ft_calloc(parse->temp_str_len + 1, sizeof(char));
	if (parse->temp_str == NULL)
		return (ft_error("Failed malloc temp_str", FAILURE));
	/*
	ft_strlcpy(parse->temp_str, &parse->token->str[parse->start_index + 1],
		parse->temp_str_len + 1);
	*/
	ft_strlcpy(parse->temp_str, &parse->token->str[parse->start_index + 1],
		parse->temp_str_len + 0);
	parse->target_ev = ft_strjoin(parse->temp_str, "=");
	if (parse->target_ev == NULL)
	{
		free(parse->temp_str);
		return (ft_error("Failed ft_strjoin target_ev", FAILURE));
	}
	free(parse->temp_str);
	if (ft_is_env(info, parse) == TRUE)
		return (TRUE);
	free(parse->target_ev);
	return (FALSE);
}

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
		= ft_strjoin(parse->old_str, &parse->token->str[parse->str_index + 1]);
	if (parse->new_str == NULL)
	{
		free(parse->target_ev);
		free(parse->ev_val);
		free(parse->old_str);
		return (ft_error("Failed ft_strjoin new_str", FAILURE));
	}
	free(parse->target_ev);
	free(parse->ev_val);
	free(parse->old_str);
	free(parse->token->str);
	parse->token->str = parse->new_str;
	return (SUCCESS);
}

static int	ft_find_env(t_info *info, t_parse *parse)
{
	//FIX: parse->str_index가 이상해짐
	//언제? 달러 뒤에 이상한거 나올때
	//-> 환경변수에 없는 게 들어왔을 때
	ft_set_quote_flag(parse);
	if (parse->squote_flag == FALSE && parse->token->str[parse->str_index]
		== '$'
		&& (ft_isalpha(parse->token->str[parse->str_index + 1])
			|| parse->token->str[parse->str_index + 1] == '_'
			|| parse->token->str[parse->str_index + 1] == '-'
			|| parse->token->str[parse->str_index + 1] == '?'))
	{
		if (ft_is_child_exit_code(parse) == TRUE)
			return (ft_convert_child_exit_code(parse));
		else if (ft_check_env(info, parse) == TRUE)
		{
			if (ft_add_env(parse) == FAILURE)
				return (FAILURE);
			parse->str_index = parse->start_index + parse->ev_val_len - 1;
		}
		else // 환경변수가 없을 때 여기로 들어와서
		/*
			bash 는 없는 환경변수를 참조하려고 하면, 해당 변수 대신 빈 문자열로 대체하고, 이후 명령어는 그 빈 문자열을 사용해 실행된다.
		*/
		{
			ft_strlcpy(&parse->token->str[parse->start_index],
				&parse->token->str[parse->str_index + 1],
				ft_strlen(parse->token->str) + 1);
			parse->str_index -= parse->temp_str_len + 1;
			// 만약 환경변수의 값이 없다면 NULL이 들어가게 됨.
			// printf("없을땐 여기로 들어오나 ? %s\n", parse->token->str);
			// printf("출력물 %s : 길이 %ld\n", parse->token->str, ft_strlen(parse->token->str));
		}
	}
	return (SUCCESS);
}

int	ft_convert_env(t_info *info, t_parse *parse)
{
	parse->token_index = 0;
	while (parse->token_index < parse->token_count)
	{
		parse->token = &parse->tokens[parse->token_index];
		parse->str_index = 0;
		while (parse->token->str[parse->str_index])
		{
			if (ft_is_heredoc(parse->token->str[parse->str_index],
					parse->token->str[parse->str_index + 1]) == TRUE)
			{
				parse->token_index++;
				break ;
			}
			if (ft_find_env(info, parse) == FAILURE)
				return (FAILURE);
			if (parse->str_index < 0)
				break ;
			parse->str_index++;
		}
		parse->token_index++;
	}
	return (SUCCESS);
}
//FIX: parse->str_index가 이상해짐
//ft_exec 부분도 같이 수정해야함
//
