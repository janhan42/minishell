/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:05:15 by janhan            #+#    #+#             */
/*   Updated: 2024/02/25 17:39:42 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_list_clear(t_list *list)
{
	list->current_node = list->front_node;
	while (list->current_node)
		ft_list_del_node(list, list->current_node);
}
