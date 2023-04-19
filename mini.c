/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:24:01 by rreis-de          #+#    #+#             */
/*   Updated: 2023/04/19 14:58:13 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_tokens(char *line)
{
    char **tokens;
    t_token *tkn;
    int i;

    tkn = NULL;
    tokens = ft_split(line, ' ');
    i = -1;
    while (tokens[++i])
        token_add_back(&tkn, tokens[i]);
    token_print(tkn);
    free_split(tokens);
    token_free(&tkn);
}

int main(int ac, char **av, char **env)
{
    char *line;
    char *str;
    //char *cwd;

    ac = 0;
    av = NULL;
    //env = NULL;
    ft_env(env);
    line = readline("/my_bash: ");
    ft_export("OLA", "/home/ola");
    ft_export("LISBOA", "/home/lisboa");
    ft_export("42", "/home/42");
    ft_export("ADEUS", "/home/adeus");
    ft_export("CASA", "/home/casa");
    env_var_print(mini()->env_vars);
    /* ft_chdir("folder");
    cwd = ft_cwd();
    printf("%s\n", cwd);
    free(cwd); */
    while (line != NULL)
    {
        add_history(line);
        str = ft_env_var("CASA");
        ft_unset("CASA");
        /* if (str)
            printf("%s\n", str); */
        //ft_tokens(line);
        free(line);
        line = readline("/my_bash: ");
    }
    env_var_print(mini()->env_vars);
    env_var_free(&mini()->env_vars);
    return (0);
}
