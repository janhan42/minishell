/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:07:27 by janhan            #+#    #+#             */
/*   Updated: 2024/03/27 19:23:23 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* print test function */
void	print_tokens(t_parse *parse)
{
	char	*type;

	printf("\n=========\n");
	for (size_t i = 0; i < parse->token_count; i++)
	{
		if (parse->tokens[i].type == WORD)
			type = "WORD";
		if (parse->tokens[i].type == PIPE)
			type = "PIPE";
		if (parse->tokens[i].type == REDIRECT)
			type = "REDIRECT";
		printf("Token%zu type = %s\n", i + 1, type);
		printf("Token%zu str = %s\n", i + 1, parse->tokens[i].str);
		printf("---------\n");
	}
	printf("Token count: %ld\n", parse->token_count);
	printf("=========\n\n");
}

/* print test function */
void	print_exec(t_exec *exec)
{
	printf("\n=========\n");
	for (size_t i = 0; i < exec->exec_arr_size; i++)
	{
		printf("cmd_path = %s\n", exec->exec_arr[i].cmd_path);
		for (size_t j = 0; exec->exec_arr[i].cmd[j] != NULL; j++)
		{
			printf("cmd[%zu] = %s\n", j, exec->exec_arr[i].cmd[j]);
		}
		printf("---------\n");
		for (size_t j = 0; ; j++)
		{
			if (exec->exec_arr[i].redirect[j].value == 0)
				break ;
			printf("redirect[%zu].type = %u\n", j, exec->exec_arr[i].redirect[j].type);
			printf("redirect[%zu].value = %s\n", j, exec->exec_arr[i].redirect[j].value);
			printf("redirect[%zu].original = %s\n", j, exec->exec_arr[i].redirect[j].original);
		}
		printf("---------\n");
	}
	printf("=========\n\n");
}

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
	if (ft_exec(info, parse, exec) == FAILURE)
		return ;
	// print_tokens(parse); // test
	// print_exec(exec); // test
	ft_free_all(parse, exec);
}

void	check(void)
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
		parse.line = readline("minishell$ ");
		if (parse.line == NULL) // 종료되어야 하는 부분
		{
			ft_list_clear(&info.mini_ev);
			ft_putstr_fd("\x1b[1A\033[11Cexit\n", STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
		if (parse.line[0] == '\0')
		{
			free(parse.line);
			continue ;
		}
		add_history(parse.line);
		ft_parse_execute(&info, &parse, &exec);
		free(parse.line);
		// atexit(check);
	}
	return (EXIT_SUCCESS);
}
