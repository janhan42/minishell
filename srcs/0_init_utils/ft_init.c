/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:39:11 by janhan            #+#    #+#             */
/*   Updated: 2024/03/16 14:53:53 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_child_exit_code;

void	ft_init(int ac, char **av, char **ev, t_info *info)
{
	g_child_exit_code = 0;
	info->ac = ac;
	info->av = av;
	info->ev = ev;
	tcgetattr(STDIN_FILENO, &info->termios_backup); // 현재 터미널 설정값을 받아옴
	ft_mini_ev_init(ev, info);
}
