/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:07:42 by janhan            #+#    #+#             */
/*   Updated: 2024/03/19 11:17:17 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/_types/_pid_t.h>
# include <sys/_types/_size_t.h>
# include <sys/termios.h>
# include <sys/syslimits.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE -1
# define CHILD_PID 0
# define IN 0
# define OUT 1
# define NONE -1

/* GLOBAL VARIABLE */
extern int	g_child_exit_code;

/* LIST STRUCT */
// 리스트 노드 구조체
typedef struct s_node
{
	void			*content;
	struct s_node	*next_node;
	struct s_node	*prev_node;
}	t_node;

// 리스트 구조체
typedef struct s_list
{
	t_node			*front_node;
	t_node			*back_node;
	t_node			*current_node;
}	t_list;

/* TOKEN STRUCT */
typedef enum e_token_type
{
	WORD, // 명령어
	PIPE, // 파이프
	REDIRECT, // 리다이렉션
}	t_token_type;

typedef struct s_token
{
	t_token_type	type; // 토큰짜른거 타입
	char			*str; // 짜른 토큰
}	t_token;

/* MAIN */
typedef struct s_info
{
	int				ac;
	char			**av;
	char			**ev;
	t_list			mini_ev; // ev전체 짜른거
	struct termios	termios_backup; // 터미널 설정 백업
	struct termios	termios; // 현재 터미널 설정
}	t_info;

typedef struct s_parse
{
	char			*line; // 전체 명령어 line
	size_t			line_index; // 명령어 인덱스
	size_t			token_count; // 토큰으로 짤랐을때 갯수
	t_token			*tokens; // 토큰들 -> 다짜름
	size_t			token_index; // 토큰의 인덱스
	t_token			*token; // 토큰 하나
	char			*temp_str; // 이거는 파서용 temp 용
	size_t			temp_str_len; // 파서용 temp 길이
	size_t			start_index; // temp의 인덱스
	size_t			str_index; // 얘도 인덱스
	int				squote_flag; // ' 플래그
	int				dquote_flag; // " 플래그
	char			*target_ev; // 명령어 실행 ev
	char			*ev_val; // $환경변수의 배열.
	size_t			ev_val_len; // ev 길이
	char			*old_str; // 파서용 저장용
	char			*new_str; // 파서용 실행용
	char			*exit_code; // 토큰 실행후 exit 값 $? 을때 저장
}	t_parse;

typedef enum s_redirect_type // 리다이렉션 타입값
{
	OUT1,
	OUT2,
	IN1,
	HERE_DOC,
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type; // 타입
	char				*value; // << < > >>
}	t_redirect;

typedef struct s_exec_info
{
	char			*cmd_path; // 실행부 명령어 경로
	char			**cmd; // 명령어
	size_t			cmd_index; // 명령어 인덱스
	t_redirect		*redirect; // 리다이렉션 정보
	size_t			redirect_index; // 리다이렉션 인덱스
	pid_t			pid; // pipe pid 값
	int				use_pipe; // 사용 여부
	int				pipe_fd[2]; // 파이프
	int				infile_fd; // fd
	int				outfile_fd; // fd
	int				builtin_parent; // 빌트인 부모 프로세스
}	t_exec_info;

typedef struct s_exec
{
	t_exec_info	*exec_arr; // 전체 명령어 실행부 리스트
	size_t		exec_arr_size; // 사이즈
	size_t		exec_arr_index; // 인덱스
	int			prev_pipe_fd; // 이전 실행부분 fd
	char		**path_ev; // ev 명령어 경로
	pid_t		current_child_pid; // 현재 실행중인 자식프로세스 pid값
}	t_exec;

/* 0_INIT UTILS */
void	ft_init(int ac, char **av, char **ev, t_info *info);
void	ft_mini_ev_init(char **ev, t_info *info);
int		ft_init_exec(t_info *info, t_parse *parse, t_exec *exec);
void	ft_sig_init(t_info *info);
void	ft_signal_2(int sig);
void	ft_sig_for_here_doc_parent(int sig);
void	ft_sig_for_here_doc_child(int sig);
void	ft_sig_for_parent(int sig);

/* 1_PARSING */
int		ft_parse(t_info *info, t_parse *parse);
int		ft_count_token(t_parse *parse);
int		ft_convert_child_exit_code(t_parse *parse);
int		ft_convert_env(t_info *info, t_parse *parse);
int		ft_make_token(t_parse *parse, t_token_type type);
int		ft_tokenization(t_parse *parse);
int		ft_syntax_check(t_parse *parse);
void	ft_remove_quote(t_parse *parse);

/* 2_exec_init */
int	ft_set_exec_info(t_parse *parse, t_exec_info *exec_info);
int	ft_make_exec_info(t_info *info, t_parse *parse, t_exec *exec);

/* 3_exec */
int		ft_check_here_doc(t_exec *exec);
int		ft_exec_builtin_parent(t_info *info, t_parse *parse, t_exec *exec, t_exec_info *exec_info);

/* 4_builtin */
int ft_cd_builtin(t_exec_info *exec_info);
int ft_echo_builtin(t_exec_info *exec_info);
int	ft_env_builtin(t_info *info);

/* 5_LIST UTILS */
t_list	ft_list_init(void);
int		ft_list_push_back(void	*content, t_list *list);
int		ft_list_del_node(t_list *list, t_node *node);
void	ft_list_clear(t_list *list);
int		ft_exit_builtin(t_list *mini_ev, t_parse *parse, t_exec *exec, t_exec_info *exec_info);
int		ft_export_builtin(t_info *info, t_exec_info *exec_info);
int		ft_pwd_builtin(void);
int		ft_unset_builtin(t_info *info, t_exec_info *exec_info);

/* 6_UTILS */
int		ft_error(char *msg, int error_code);
void	ft_free_tokens(t_parse *parse, size_t token_size);
int		ft_is_child_exit_code(t_parse *parse);
int		ft_is_quote(char c);
int		ft_is_operator(char c);
int		ft_is_redirect(char c);
int		ft_is_space(char c);
int		ft_is_heredoc(char c1, char c2);
int		ft_is_env(t_info *info, t_parse *parse);
int		ft_is_builtin_parent(t_exec *exec, t_exec_info *exec_info);
int		ft_is_builtin(t_exec_info *exec_info);
int		ft_perror(int error_code);
void	ft_free_exec(t_exec *exec, size_t exec_arr_i);
void	ft_free_all(t_parse *parse, t_exec *exec);
#endif
