/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:48:25 by janhan            #+#    #+#             */
/*   Updated: 2024/03/20 18:15:53 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	ft_list_init(void)
{
	t_list	result;

	result.front_node = NULL;
	//result.back_node = NULL;
	//result.current_node = NULL;
	return (result);
}
