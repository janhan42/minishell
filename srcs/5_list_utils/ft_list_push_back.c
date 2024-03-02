/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:49:35 by janhan            #+#    #+#             */
/*   Updated: 2024/02/24 01:17:40 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_list_push_back(void	*content, t_list *list)
{
	t_node	*new_node;

	if (list == NULL || content == NULL)
		return (ft_error("argument han been wrong", FAILURE));
	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return (ft_error("new_node malloc return NULL", FAILURE));
	new_node->content = content;
	new_node->next_node = NULL;
	new_node->prev_node = list->back_node;
	if (new_node->prev_node != NULL)
		new_node->prev_node->next_node = new_node;
	if (list->front_node == NULL)
	{
		list->front_node = new_node;
		list->back_node = new_node;
		list->current_node = new_node;
		return (SUCCESS);
	}
	list->back_node = new_node;
	return (SUCCESS);
}
