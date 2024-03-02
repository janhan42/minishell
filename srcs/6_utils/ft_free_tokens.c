/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:23:10 by janhan            #+#    #+#             */
/*   Updated: 2024/02/27 23:23:55 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stddef.h>

void	ft_free_tokens(t_parse *parse, size_t token_size)
{
	size_t	i;

	i = 0;
	while (i < token_size)
	{
		free(parse->tokens[i].str);
		i++;
	}
	free(parse->tokens);
}
