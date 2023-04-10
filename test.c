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

int main(void)
{
    char *line;
    char **tokens;
    t_token *tkn;
    int i;

    tkn = NULL;
    line = readline("/my_bash: ");
    tokens = ft_split(line, ' ');
    i = -1;
    while (tokens[++i])
        token_add_back(&tkn, tokens[i]);
    token_print(tkn);
    return (0);
}

/* int main(void)
{
    char *line;
    t_token *tkn;
    int i;

    i = 0;
    tkn = NULL;
    line = readline("/my_bash: ");
    if (strlen(line) > 0)
            add_history(line);
    token_add_back(&tkn, line);
    while (i < 5)
    {
        line = readline("/my_bash: ");
        if (line != NULL && strlen(line) > 0)
        {
            token_add_back(&tkn, line);
            add_history(line);
        }
        i++;
    }
    token_print(tkn);
    return (0);
} */