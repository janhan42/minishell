/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:44:53 by janhan            #+#    #+#             */
/*   Updated: 2024/03/15 11:07:04 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signal_handler(int signal)
{
	printf("Recived signal %d\n", signal);
	// 필요 처리 구현
	return ;
}

int main(void)
{
	signal(SIGINT, signal_handler);

	while (1)
		sleep(1);
	return (0);
}
