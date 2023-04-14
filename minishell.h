/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:23:59 by rreis-de          #+#    #+#             */
/*   Updated: 2023/04/10 16:24:00 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env_var
{
    char *var;
    char *exp;
    struct s_env_var *next;
}   t_env_var;

typedef struct s_cmd
{
    int  type;
    char **args;
    char *gpath; 
    int fd[2];
    int in_fd;
    int out_fd;
    struct s_cmd *next;
}   t_cmd;

typedef struct s_token
{
    char    *str;
    int     type;
    struct s_token *next;
}   t_token;

typedef struct s_mini
{
    struct s_env_var *env_vars;
}   t_mini;


void    ft_tokens(char *line);

int ft_strlen(char *str);
char    *str_join(char *old, char *seg);
int ft_strcmp(char *s1, char *s2);
void    free_split(char **arr);
t_mini  *mini(void);

void    token_add_back(t_token **tkn, char *str);
t_token    *token_new(char *str);
t_token *token_last(t_token *tkn);
void    token_print(t_token *tkn);
void    token_free(t_token **tkn);

void    env_var_add_back(t_env_var **lst, char *var, char *exp);
t_env_var   *env_var_new(char *var, char *exp);
t_env_var   *env_var_last(t_env_var *lst);
void    env_var_print(t_env_var *lst);
void    env_var_free(t_env_var **lst);
char    *search_env_var(char *var);
void    remove_env_var(char *var);

char	**ft_split(char const *s, char c);
char	*word(char const *str, int *ptr_i, char c);
int	string_counter(char const *str, char c);

char    *ft_cwd();
void    ft_chdir(char *dir);
char    *ft_env_var(char *str);
void    ft_export(char *var, char *exp);
void    ft_unset(char *var);

int ft_cmds(t_cmd *cmds, char **env);
int ft_exec(t_cmd *cmd, char **env);
int ft_builtin(t_cmd *cmd);

#endif