/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:24:03 by rreis-de          #+#    #+#             */
/*   Updated: 2023/04/10 16:24:04 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    token_add_back(t_token **tkn, char *str)
{
    t_token *new;
    t_token *last;

    new = token_new(str);
    if (*tkn)
    {
        last = token_last(*tkn);
        last->next = new;
    }
    else
        *tkn = new;
}

t_token    *token_new(char *str)
{
    t_token *elem;

    elem = (t_token *)malloc(sizeof(*elem));
    if (!elem)
        return (NULL);
    elem->str = str;
    elem->next = NULL;
    return (elem);
}

t_token *token_last(t_token *tkn)
{
    t_token *last;

    last = tkn;
    while (tkn != NULL)
    {
        last = tkn;
        tkn = tkn->next;
    }
    return (last);
}

void    token_print(t_token *tkn)
{
    while (tkn)
    {
        printf("%s\n", tkn->str);
        tkn = tkn->next;
    }
}