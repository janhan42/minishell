/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:13:07 by janhan            #+#    #+#             */
/*   Updated: 2024/03/20 17:36:38 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief
 * signal 'SIGINT'핸들러 부분
 * @param sig
 */
void	ft_signal_2(int sig)
{
	(void)sig;
	g_child_exit_code = 1;
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1); // 버퍼를 빈문자열로 변경
	rl_redisplay(); // 바로 화면상에 적용
}

/**
 * @brief
 * termios 설정에서 siganl컨트롤 부분 설정 init
 * @param info
 * info->termios.c_flag = ~ECHOCTL 은 기존 프로그램 실행중 Ctrl+C ^C문자를 안나오게 설정.
 * tcsetattr 은 info->termios.c_lflag 를 변경한 사항을 즉시 적용하는 코드 (TCSANOW)
 *
 *
 */
void	ft_sig_init(t_info *info)
{
	info->termios = info->termios_backup; //백업의 복사본
	info->termios.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &info->termios);
	signal(SIGINT, ft_signal_2); // Ctrl+C -> 기존명령어플러시
	signal(SIGQUIT, SIG_IGN); // Ctrl+"\" -> dose noting
}

void	ft_sig_for_here_doc_parent(int sig)
{
	(void)sig;
	printf("\n");
}

void	ft_sig_for_here_doc_child(int sig)
{
	(void)sig;
	exit(1);
}

void	ft_sig_for_parent(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
	}
	if (sig == SIGQUIT)
	{
		printf("^\\Quit: %d\n", sig);
	}
}
