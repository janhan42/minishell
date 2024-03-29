/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:17:07 by janhan            #+#    #+#             */
/*   Updated: 2024/03/16 15:40:07 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief
 * pipe, redirection 체크용
 * @param c
 * @return int
 */
int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
