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

typedef struct s_token
{
    char    *str;
    struct s_token *next;
}   t_token;


int ft_strlen(char *str);
char    *str_join(char *old, char *seg);

void    token_add_back(t_token **tkn, char *str);
t_token    *token_new(char *str);
t_token *token_last(t_token *tkn);
void    token_print(t_token *tkn);

char	**ft_split(char const *s, char c);
char	*word(char const *str, int *ptr_i, char c);
int	string_counter(char const *str, char c);

char    *ft_cwd();
void    ft_chdir(char *dir);
char    *ft_env_var(char *str);

#endif