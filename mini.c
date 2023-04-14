/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:24:01 by rreis-de          #+#    #+#             */
/*   Updated: 2023/04/10 16:34:46 by rreis-de         ###   ########.fr       */
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

int main(void)
{
    char *line;
    char *str;

    line = readline("/my_bash: ");
    while (line != NULL)
    {
        add_history(line);
        ft_export("CASA", "/home/casa");
        str = ft_env_var("CASA");
        ft_unset("CASA");
        if (str)
            printf("%s\n", str);
        //ft_tokens(line);
        free(line);
        line = readline("/my_bash: ");
    }
    return (0);
}
