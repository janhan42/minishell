/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:32:02 by janhan            #+#    #+#             */
/*   Updated: 2024/02/27 23:36:41 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_make_token(t_parse *parse, t_token_type type)
{
	parse->tokens[parse->token_index].type = type;
	parse->temp_str
		= (char *)ft_calloc(parse->line_index - parse->str_index + 2, sizeof(char));
	if (parse->temp_str == NULL)
		return (ft_error("Failed calloc temp_str", FAILURE));
	ft_strlcpy(parse->temp_str, &parse->line[parse->start_index], parse->line_index - parse->start_index + 2);
	parse->tokens[parse->token_index].str = parse->temp_str;
	parse->token_index++;
	return (SUCCESS);
}
