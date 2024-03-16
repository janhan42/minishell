/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:07:27 by janhan            #+#    #+#             */
/*   Updated: 2024/03/16 18:11:13 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief
 * 사실상 메인
 * @param info info 구조체 (기본 구조체)
 * @param parse parse 구조체 (파싱부)
 * @param exec  exec 구조체 (실행부)
 */
static void	ft_parse_execute(t_info *info, t_parse *parse, t_exec *exec)
{
	if (ft_parse(info, parse) == FAILURE)
		return ;
	if (ft_make_exec_info(info, parse, exec) == FAILURE)
		return ;
	for (size_t i = 0; i < parse->token_count; i++)
	{
		printf("tokens %d -> %s\n", parse->tokens[i].type, parse->tokens[i].str);
	}
	for (size_t i = 0; i < parse->token_count; i++)
	{
		printf("token %d -> %s\n", parse->token[i].type, parse->token[i].str);
	}

	// if (ft_exec(info, parse, exec) == FAILURE)
	// 	return ;
	// ft_free_all(parse, exec);
}

void check(void)
{
	system("leaks minishell");
}
int	main(int ac, char **av, char **ev)
{
	t_info		info;
	t_parse		parse;
	t_exec		exec;

	ft_init(ac, av, ev, &info);
	while (TRUE)
	{
		ft_sig_init(&info);
		parse.line = readline("\033");
		if (parse.line == NULL) // 명령어가 없을때 exit Ctrl+D
		{
			ft_list_clear(&info.mini_ev);
			ft_putstr_fd("\x1b[1A\033[9Cexit\n", STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
		if (parse.line[0] == '\0')
		{
			free(parse.line);
			continue ;
		}
		add_history(parse.line); // 히스토리 저장
		ft_parse_execute(&info, &parse, &exec); // 사실상 메인
		free(parse.line);
	}
	return (EXIT_SUCCESS);
}
