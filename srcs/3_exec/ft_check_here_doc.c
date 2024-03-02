/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:36:06 by janhan            #+#    #+#             */
/*   Updated: 2024/03/02 15:17:29 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_get_here_doc(t_redirect *redirect)
{
	char	*input;
	char	*limiter;
	int		temp_fd;

	temp_fd = open("/tmp/temp_fd", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (temp_fd == FAILURE)
		exit(ft_perror(errno));
	while (TRUE)
	{
		write(1, "> ", 2);
		input = get_next_line(STDIN_FILENO);
		if (!input || ft_strncmp(input, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(temp_fd, input, ft_strlen(input));
		free(input);
	}
	free(input);
	free(limiter);
	if (close(temp_fd) == FAILURE)
		exit(ft_perror(errno));
}

static void	ft_search_here_doc(t_exec *exec)
{
	t_exec_info	*exec_info;
	t_redirect	*redirect;

	signal(SIGINT, ft_sig_for_here_doc_child);
	exec->exec_arr_index = 0;
	while (exec->exec_arr_index < exec->exec_arr_size)
	{
		exec_info = &exec->exec_arr[exec->exec_arr_index];
		exec_info->redirect_index = 0;
		while (exec_info->redirect[exec_info->redirect_index].value != 0)
		{
			redirect = &exec_info->redirect[exec_info->redirect_index];
			if (redirect->type == HERE_DOC)
				ft_get_here_doc(redirect);
			exec_info->redirect_index++;
		}
		exec->exec_arr_index++;
	}
}

int	ft_check_here_doc(t_exec *exec)
{
	pid_t	here_doc_pid;
	int		child_status;

	here_doc_pid = fork();
	if (here_doc_pid == FAILURE)
		return (FAILURE);
	else if (here_doc_pid == CHILD_PID)
		ft_search_here_doc(exec);
	signal(SIGINT, ft_sig_for_here_doc_parent);
	if (waitpid(-1, &child_status, 0) == FAILURE)
		return (ft_perror(FAILURE));
	g_child_exit_code = WEXITSTATUS(child_status);
	if (g_child_exit_code != EXIT_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
