/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:03:14 by janhan            #+#    #+#             */
/*   Updated: 2024/02/28 00:32:24 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_ready_tokenization(t_parse *parse)
{
	parse->line_index = 0;
	parse->tokens = (t_token *)ft_calloc(parse->token_count, sizeof(t_token));
	if (parse->tokens == NULL)
		return (ft_error("Failed calloc tokens", FAILURE));
	return (SUCCESS);
}

static void	ft_parse_init(t_parse *parse)
{
	parse->line_index = 0;
	while (ft_is_space(parse->line[parse->line_index]))
		parse->line_index++;
	parse->token_count = 0;
	parse->token_index = 0;
	parse->start_index = 0;
	parse->str_index = 0;
	parse->squote_flag = FALSE;
	parse->dquote_flag = FALSE;
}
int	ft_parse(t_info *info, t_parse *parse)
{
	ft_parse_init(parse);
	if (ft_count_token(parse) == FAILURE)
		return (FAILURE);
	if (ft_ready_tokenization(parse) == FAILURE)
		return (FAILURE);
	if (ft_tokenization(parse) == FAILURE)
	{
		ft_free_tokens(parse, parse->token_index);
		return (FAILURE);
	}
	if (ft_convert_env(info, parse) == FAILURE)
	{
		ft_free_tokens(parse, parse->token_count);
		return (FAILURE);
	}
	ft_remove_quote(parse);
	if (ft_syntax_check(parse) == FAILURE)
	{
		parse->token_index = parse->token_count;
		ft_free_tokens(parse, parse->token_count);
		return (FAILURE);
	}
	return (SUCCESS);
}
