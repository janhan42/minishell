/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:44:53 by janhan            #+#    #+#             */
/*   Updated: 2024/03/13 10:55:04 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int	main(int argc, char **argv, char **enpv)
{
	char *input;

	while (TRUE)
	{
		input = readline("명령어를 입력하세요: ");

		if (input)
		{
			printf("입력된 명령어: %s\n", input);

			add_history(input);
			free(input);
		}
	}
	return (0);
}
