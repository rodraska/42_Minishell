/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:54:04 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 17:31:46 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include<stddef.h>
# include<limits.h>
# include<readline/readline.h>
# include<readline/history.h>

// Signal libraries
# include<signal.h>
# include<stdarg.h>
# include<dirent.h>
# include<sys/types.h>
# include<sys/stat.h>

# define STATUS_ERROR 1
# define STATUS_SUCCESS 0
# define STATUS_SYNTAX_ERROR 3
# define UNEXPECTED_TOKEN "bash: syntax error near unexpected token `|'"
//# define H printf("HERE\n")
// # define T printf("THERE\n")

typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;
typedef struct s_terminal	t_terminal;
typedef struct s_expo		t_expo;
typedef struct s_token		t_token;

struct s_terminal
{
	char			**env;
	t_expo			*expo;
	char			*path;
	int				status;
	int				childs;
	int				heredoc;
	int				stopheredoc;
	int				in_cmd;
	int				agoravai;
	t_cmd			*list;
};

struct s_cmd
{
	char			*str;
	t_token			*tokens;
	char			**args;
	char			*gpath;
	int				is_type;
	int				fd_master[2];
	int				fd[2];
	int				pid;
	int				status;
	int				(*execute)(t_cmd *cmd, int in);
	int				stop;
	int				here_fd[2];
	t_cmd			*next;
};

struct s_expo
{
	char			*variable;
	char			*value;
	t_expo			*next;
};

struct s_token
{
	char			*str;
	t_token			*next;
};

void					signals_call(void);
//-----------parsing----------------------//
int						check_sintaxe(const char *s, int spa, int i, int j);
int						ft_phrases(const char *line);

void					create_str(char *new, char *s, int i, char set);
void					separator_cmd(char **new, char **s, int *i, int j);
int						is_separator_here(const char *s, int *j);
char					*ft_strjoin_expansion(char *line, char *buf);
char					*ft_strjoin_char(char *line, char c);
int						check_sintaxe(const char *s, int spa, int i, int j);

//-----------tokens----------------------//
t_cmd					*create_list_tokens(char **arr);
void					token_add_back(t_token **root, char *str);
void					token_remove(t_token **root, t_token *elem);
void					ft_tokens(t_token **token, char *phrase, int i);
t_cmd					*insert_end_tokens(t_cmd **root, char *s, t_cmd *end);
void					token_print(t_token *curr);
void					clean_tokens(t_token *list);
void					clean_redirect_tokens(t_token **list);

//-----------path------------------------------//
char					*path_join(char *s1, char *s2);
char					*get_path(char **env, char *str);
char					*get_gpath(char **env, char **args);

//-----------expander--------------------//
int						check(char c);
char					*expander(char *str, char sep);
char					*dollar(char *str, int *flag);
void					expander_args(t_cmd *list, int flag);
char					*find_needle(char *stack, char *needle, char set);

//-----------expander2--------------------//
int						check(char c);
char					*dollar(char *str, int *flag);
char					*remove_quotes(char *str);
char					*find_needle2(char *stack, char *l, char set, int i);
char					*find_needle(char *stack, char *needle, char set);
int						check_interrogation(char *str);

//----------calloc-----//
void					*malloc_ob(size_t length);

//---------comands-----//
char					**create_array_cmds(t_token *list);
void					build_cmds_list(t_cmd **list, t_cmd	*tmp);
void					cmd_redirect(t_cmd *cmd, int f, int fd);
void					clean_redirect_tokens(t_token **list);

//---------comands2-----//
int						redirect_pai(t_token *tmp, t_cmd *cmd, int fd, int f);
int						redirect_1(t_token *tmp, t_cmd *cmd, int fd);
int						redirect_2(t_token *tmp, t_cmd *cmd, int fd);
int						redirect_4(t_token *tmp, t_cmd *cmd, int fd);

//---------clean-------//
void					clean_expo(t_expo *list);

//---------ft_replace---------------//
int						check_contain(char *origin, char *set);
int						contain_char(char *s, char c);
int						ft_compare(const char *s1, const char *s2);
char					*ft_replace(char *dst, char *to, char *rep);

//-----------ft_split---------//
char					**ft_split(char const *s, char c);
void					free_2d(char **result);
//----------ft_subtring--------//
char					*ft_substring(const char *str, int start, int end);

//----------helpers------//
int						is_quote(char c);

int						is_separator(const char *s, int *j);
int						is_redirect(const char *s);
int						is_space(char c);
void					put_str(char *s);
int						ft_isalpha(char c);
int						ft_isnum(char c);
int						check_group(char c);

//----------linked_list----------//
int						cnt_rec(t_token *node);
int						cnt_here(t_cmd *node);
int						cnt(t_expo *node);
void					deallocate(t_cmd *curr);
void					*get_function(char *name);
t_cmd					*insert_end(t_cmd **root, t_cmd *end);
void					insert_end_list(t_expo **root, char *value);
void					print_linked(t_cmd *curr);

//----------utils----------//
size_t					ft_strlen(const char *a, char set);
char					*ft_strcpy(char *dest, char *src);
char					*ft_strcat(char *dest, char *src);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strdup(const char	*s1);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//          Execution

//----------Builtin----------------------//
int						execute_cd(t_cmd *cmd);
int						execute_echo(t_cmd *cmd);
int						execute_env(t_cmd *cmd);
int						execute_export(t_cmd *cmd);
int						execute_pwd(t_cmd *cmd);
int						execute_unset(t_cmd *cmd);
int						execute_exit(t_cmd *cmd, int len_cmd);

//-----------execute----------------------------//
int						execute_redirection_out(t_cmd *cmd);
int						execute_redirection_append_out(t_cmd *cmd);
int						ft_heredoc(t_cmd *cmd, char *delimiter, \
char *buf, int len);
char					*ft_strjoin_rodraska(char *line, char *buf);
int						execute_main(t_cmd *cmd, int in, int out);
int						execute_geral(t_cmd *cmd, int in, int out);
int						execute_default(t_cmd *cmd);
void					ft_wait(t_cmd *cmd);
void					cleanall(t_cmd *list, int f);

// --------utils_exe---------------------//
char					**clone_env(char **env);
char					**increase_env(char **env);
int						ft_strncmp(char *s1, char *s2, int n);
char					*str_join(char *old, char *seg, char c);
int						ft_strlen_2d(char **a);
char					*find_var(char *var);
int						ft_atoi(const char *str, int res, int i, int sign);
int						especial_case(const char *s);

void					print_list(t_expo *node);
void					print_list2(t_expo *node, t_cmd *cmd);
int						ft_strcmp(const char *s1, const char *s2);
void					swap_content(char **node, char **node1);
void					bubblesort(t_expo *root);
t_expo					*insert_end_expo_list(t_expo **t, char *s, t_expo **l);
t_expo					*create_expo(char **env);
char					**sync_e(char *cmd, int i, int fu);
char					**syncadd(char **env, char *cmd);
char					*remove_quotes(char *str);
char					*put_quotes(char *str);
int						env_variable_replaced(char *cmd, int *flag);
char					*ft_itoa(int n);
void					close_shit(t_cmd *cmd);
int						export_variable_name(char *cmd);
int						execute_directory(t_cmd *cmd, int fd);

int						status(t_cmd *cmd, int status);
void					*free_ob(void *p, void *resul);

extern t_terminal			g_terminal;

#endif
