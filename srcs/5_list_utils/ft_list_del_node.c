/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:06:02 by janhan            #+#    #+#             */
/*   Updated: 2024/03/27 15:20:37 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
static void	ft_del_node(t_node *node)
{
	t_node	*node1;
	t_node	*node2;

	node1 = node->prev_node;
	node2 = node->next_node;
	free(node->content);
	free(node);
	node1->next_node = node2;
	node2->prev_node = node1;
}

static void	ft_del_front_node(t_list *list, t_node *node)
{
	t_node	*node_temp;

	node_temp = node->next_node;
	node_temp->prev_node = NULL;
	free(node->content);
	free(node);
	list->back_node = node_temp;
	list->current_node = list->front_node;
}

static void	ft_del_back_node(t_list *list, t_node *node)
{
	t_node	*node_temp;

	node_temp = node->prev_node;
	node_temp->next_node = NULL;
	free(node->content);
	free(node);
	list->back_node = node_temp;
	list->current_node = list->front_node;
}

static void	ft_del_cur_node(t_list *list, t_node *node)
{
	ft_del_node(node);
	list->current_node = list->front_node;
}

int	ft_list_del_node(t_list *list, t_node *node)
{
	if (list == NULL || node == NULL)
		return (ft_error("argument has been wrong", FAILURE));
	if (node->next_node == NULL && node->prev_node == NULL)
	{
		free(node->content);
		free(node);
		*list = ft_list_init();
		return (SUCCESS);
	}
	if (list->front_node == node)
		ft_del_front_node(list, node);
	else if (list->back_node == node)
		ft_del_back_node(list, node);
	else if (list->current_node == node)
		ft_del_cur_node(list, node);
	else
		ft_del_node(node);
	return (SUCCESS);
}
*/

int	ft_list_del_node(t_list *list, t_node *node)
{
	t_node	*finder;

	finder = list->front_node;
	if (list == NULL || node == NULL)
		return (ft_error("argument has been worng", FAILURE));
	if (list->front_node == node) // 첫 노드가 지워야 하는 노드일 때
	{
		list->front_node = node->next_node;
		free(node->content);
		free(node);
		return (SUCCESS);
	}
	while (finder != node && finder->next_node != node) // 노드 찾기
		finder = finder->next_node;
	finder->next_node = node->next_node;
	// 찾은 노드의 next_node를 지워야 하는 노드의 next_node로 바꿔줌
	free(node->content);
	free(node);
	node = 0;
	return (SUCCESS);
	// 첫 노드가 지워야 하는 거일 때 조건 추가
}
