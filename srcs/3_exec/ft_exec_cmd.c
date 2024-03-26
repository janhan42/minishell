/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:01:16 by janhan            #+#    #+#             */
/*   Updated: 2024/03/26 14:05:23 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_make_path(t_exec_info *exec_info, char *path)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (temp == NULL)
		exit(EXIT_FAILURE);
	result = ft_strjoin(temp, exec_info->cmd_path);
	if (result == NULL)
	{
		free(temp);
		exit(EXIT_FAILURE);
	}
	free(temp);
	return (result);
}

static int	ft_find_cmd(t_exec *exec, t_exec_info *exec_info)
{
	size_t	i;
	char	*cmd_path;

	cmd_path = exec_info->cmd_path;
	ft_cmd_is_directory(cmd_path);
	if (cmd_path == NULL/* || access(cmd_path, X_OK) == SUCCESS*/)
		return (SUCCESS);
	if (cmd_path[0] == '\0') //FIX: cmd_path가 빈문자열이면 cmd_path랑 cmd배열 바꿔주기
		exit(SUCCESS);
	i = 0;
	while (exec->path_ev[i])
	{
		cmd_path = ft_make_path(exec_info, exec->path_ev[i]);
		if (access(cmd_path, X_OK) == SUCCESS)
		{
			exec_info->cmd_path = cmd_path;
			return (SUCCESS);
		}
		free(cmd_path);
		i++;
	}
	return (FAILURE);
}

static void	ft_set_fd(t_exec *exec, t_exec_info *exec_info)
{
	ft_set_pipe_fd(exec, exec_info);
	ft_set_redirect_fd(exec_info);
	if (exec_info->infile_fd != NONE)
	{
		if (dup2(exec_info->infile_fd, STDIN_FILENO) == FAILURE)
			exit(ft_perror(errno));
		if (close(exec_info->infile_fd) == FAILURE)
			exit(ft_perror(errno));
	}
	if (exec_info->outfile_fd != NONE)
	{
		if (dup2(exec_info->outfile_fd, STDOUT_FILENO) == FAILURE)
			exit(ft_perror(errno));
		if (close(exec_info->outfile_fd) == FAILURE)
			exit(ft_perror(errno));
	}
}

static char	**ft_make_envp(t_list *mini_envp)
{
	char	**envp;
	size_t	count;
	t_node	*node;

	count = 0;
	node = mini_envp->front_node;
	while (node->next_node != NULL)
	{
		count++;
		node = node->next_node;
	}
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (envp == NULL)
		exit(ft_error("envp malloc failed\n", EXIT_FAILURE));
	count = 0;
	node = mini_envp->front_node;
	while (node->next_node != NULL)
	{
		envp[count] = (char *)node->content;
		node = node->next_node;
		count++;
	}
	envp[count] = NULL;
	return (envp);
}

void	ft_exec_cmd(t_info *info, t_parse *parse,
	t_exec *exec, t_exec_info *exec_info)
{

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	/*
	char	*path_ev;
	path_ev = (char *)list_content_finder(info->mini_ev.front_node, "PATH");
	*/
	if (ft_find_cmd(exec, exec_info) == FAILURE
		&& ft_is_builtin(exec_info) == FALSE)
	{
		printf("%s\n", exec_info->cmd_path);
		ft_printf_err("%s: command not found\n", exec_info->cmd[0]);
		ft_free_all(parse, exec);
		exit(127);
	}
	else
	{
		if (exec_info->cmd[parse->token_count - 1] != NULL
			&& exec_info->cmd[parse->token_count - 1][0] == '\0')
			exec_info->cmd[parse->token_count - 1] = NULL;
		ft_set_fd(exec, exec_info);
		if (exec_info->cmd_path == NULL)
			exit(EXIT_SUCCESS);
		if (ft_is_builtin(exec_info) == TRUE)
			ft_exec_builtin(info, parse, exec, exec_info);
		else
			execve(exec_info->cmd_path, exec_info->cmd,
				ft_make_envp(&info->mini_ev));
	}
}
