/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:14:40 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 10:31:09 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_quote(char c)
{
	if (c == '\"')
		return (1);
	else if (c == '\'')
		return (2);
	return (0);
}

int	is_redirect(const char *s)
{
	if (s[0] == '<' && s[1] == '<')
		return (3);
	else if (s[0] == '>' && s[1] == '>')
		return (4);
	else if (s[0] == '<')
		return (1);
	else if (s[0] == '>')
		return (2);
	return (0);
}

int	is_separator(const char *s, int *j)
{
	if (s[0] == '>' && s[1] == '>')
		*j = (2);
	else if (s[0] == '<' && s[1] == '<')
		*j = (2);
	else if (s[0] == '>')
		*j = (1);
	else if (s[0] == '<')
		*j = (1);
	else if (s[0] == '|')
		*j = (1);
	else
		*j = 0;
	return (*j);
}
