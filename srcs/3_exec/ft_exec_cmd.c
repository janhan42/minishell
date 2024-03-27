/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:01:16 by janhan            #+#    #+#             */
/*   Updated: 2024/03/27 22:58:10 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stddef.h>

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
/**
 * @brief
 * make path and access_path
 * @param exec
 * @param exec_info
 * @return int FAILURE or SUCCESS
 */
static int	ft_access_path(t_exec *exec, t_exec_info *exec_info)
{
	size_t	i;
	char	*cmd_path;

	cmd_path = exec_info->cmd_path;
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
/*
	TODO: export PATH=  해서 PATH값을 비운 후에, cat, ls 같은거 했을 때 ‘No such file or directory’ 에러가 나와야 함.
*/
static int	ft_find_cmd(t_exec *exec, t_exec_info *exec_info, t_parse *parse)
{
	char	*cmd_path;

	cmd_path = exec_info->cmd_path;
	if (cmd_path == NULL /*access(cmd_path, X_OK) == SUCCESS*/)
		return (SUCCESS); // ls를 path에서 안찾아서 access 주석했음 ㅅㅂ
	if (cmd_path[0] == 0)
	{
		ft_printf_err("%s: command not found\n", exec_info->cmd[0]);
		ft_free_all(parse, exec);
		exit(127);
	}
	if ((cmd_path[0] == '.' && cmd_path[1] == '/' ) || cmd_path[0] == '/')
	{
		ft_cmd_is_directory(cmd_path);
		if (access(cmd_path, F_OK) == FAILURE)
		{
			ft_printf_err("minishell: %s: No such file or directory\n", exec_info->cmd[0]);
			exit(127);
		}
		if (access(cmd_path, X_OK) == FAILURE)
		{
			ft_printf_err("minishell: %s: Permission denied\n", exec_info->cmd[0]);
			exit(126);
		}
		if (access(cmd_path, X_OK) == SUCCESS)
			return (SUCCESS);
	}
	if (exec->path_ev[0] == NULL && !ft_is_builtin(exec_info))
	{
		ft_printf_err("minishell: %s: No such file or directory\n", exec_info->cmd[0]);
		ft_free_all(parse, exec);
		exit(127);
	}
	if (ft_access_path(exec, exec_info) == SUCCESS)
		return (SUCCESS);
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
/*
char	*path_ev;
path_ev = (char *)list_content_finder(info->mini_ev.front_node, "PATH");
*/
void	ft_exec_cmd(t_info *info, t_parse *parse,
	t_exec *exec, t_exec_info *exec_info)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_find_cmd(exec, exec_info, parse) == FAILURE
		&& ft_is_builtin(exec_info) == FALSE)
	{
		ft_printf_err("%s: command not found\n", exec_info->cmd[0]);
		printf ("%s\n", exec_info->cmd[0]);
		ft_free_all(parse, exec);
		exit(127);
	}
	else // 이거 누가 넣음 TODO: cat | cat | cat 오버플로우 남
	{
		/*
		printf("parse->token_count = %ld\n", parse->token_count);
		printf("exec_info->cmd_index = %ld\n", exec_info->cmd_index);
		printf("exec_info->use_pipe = %d\n", exec_info->use_pipe);
		*/
		if (exec_info->use_pipe == 1)
			if (exec_info->cmd[exec_info->cmd_index - 1] != NULL
				&& exec_info->cmd[exec_info->cmd_index - 1][0] == '\0')
				exec_info->cmd[exec_info->cmd_index - 1] = NULL;
		if (exec_info->cmd[exec_info->cmd_index] != NULL
			&& exec_info->cmd[exec_info->cmd_index][0] == '\0')
			exec_info->cmd[exec_info->cmd_index] = NULL;
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
