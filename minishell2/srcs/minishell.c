/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:44:53 by janhan            #+#    #+#             */
/*   Updated: 2024/03/16 15:33:55 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/termios.h>

void	ft_signal_2(int sig)
{
	(void)sig;
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int main(void)
{
	struct termios termios_backup;


	tcgetattr(STDIN_FILENO, &termios_backup);
	termios_backup.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_backup);
	signal(SIGINT, ft_signal_2);
	signal(SIGQUIT, SIG_IGN);
	char *temp;
	while (1)
	{
		temp = readline("\033");
		if (temp == NULL) // Ctrl+D ???
		{
			printf("\x1b[1Aexit\n"); // \x1b[1A 는 한줄위로 올라간뒤 출력
			return (EXIT_SUCCESS);
		}
		// if (temp[0] == '\0')
		// {
		// 	free(temp);
		// 	continue ;
		// }
		add_history(temp); // 시스템상 히스토리에 저장
	}
	return (0);
}
