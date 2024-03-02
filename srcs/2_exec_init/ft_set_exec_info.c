/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_exec_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:10:50 by janhan            #+#    #+#             */
/*   Updated: 2024/03/01 19:21:51 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stddef.h>

static int	ft_malloc_cmd(t_parse *parse, t_exec_info *exec_info)
{
	size_t	token_index;
	size_t	size;

	token_index = parse->token_index;
	size = 0;
	while (token_index < parse->token_count)
	{
		if (parse->tokens[token_index].type == PIPE)
			break ;
		if (parse->tokens[token_index].type == REDIRECT)
			token_index++;
		if (parse->tokens[token_index].type == WORD)
			size++;
		token_index++;
	}
	exec_info->cmd = (char **)ft_calloc(size + 1, sizeof(char *));
	if (exec_info->cmd == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_malloc_redirect(t_parse *parse, t_exec_info *exec_info)
{
	size_t	tokens_index;
	size_t	size;

	tokens_index = parse->token_index;
	size = 0;
	while (tokens_index < parse->token_count)
	{
		if (parse->tokens[tokens_index].type == PIPE)
			break ;
		if (parse->tokens[tokens_index].type == REDIRECT)
			size++;
		tokens_index++;
	}
	exec_info->redirect = (t_redirect *)ft_calloc(size + 1, sizeof(t_redirect));
	if (exec_info->redirect == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static void	ft_add_cmd(t_parse *parse, t_exec_info *exec_info)
{
	exec_info->cmd[exec_info->cmd_index] = parse->tokens[parse->token_index].str;
	if (exec_info->cmd_index == 0)
		exec_info->cmd_path = exec_info->cmd[exec_info->cmd_index];
	exec_info->cmd_index++;
}

static void	ft_add_redirect(t_parse *parse, t_exec_info *exec_info)
{
	if (ft_strncmp(parse->tokens[parse->token_index].str, ">", 2) == 0)
		exec_info->redirect[exec_info->redirect_index].type = OUT1;
	else if (ft_strncmp(parse->tokens[parse->token_index].str, ">>", 3) == 0)
		exec_info->redirect[exec_info->redirect_index].type = OUT2;
	else if (ft_strncmp(parse->tokens[parse->token_index].str, "<<", 3) == 0)
		exec_info->redirect[exec_info->redirect_index].type = HERE_DOC;
	exec_info->redirect[exec_info->redirect_index].value
		=	parse->tokens[parse->token_index + 1].str;
	exec_info->redirect_index++;
}

int	ft_set_exec_info(t_parse *parse, t_exec_info *exec_info)
{
	if (ft_malloc_cmd(parse, exec_info) == FAILURE)
		return (FAILURE);
	if (ft_malloc_redirect(parse, exec_info) == FAILURE)
		return (FAILURE);
	while (parse->token_index < parse->token_count)
	{
		if (parse->tokens[parse->token_index].type == PIPE)
		{
			exec_info->use_pipe = TRUE;
			parse->token_index++;
			break ;
		}
		if (parse->tokens[parse->token_index].type == WORD)
			ft_add_cmd(parse, exec_info);
		if (parse->tokens[parse->token_index].type == REDIRECT)
		{
			ft_add_redirect(parse, exec_info);
			parse->token_index++;
		}
		parse->token_index++;
	}
	return (SUCCESS);
}
