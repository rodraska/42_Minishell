/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:14:40 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 10:13:22 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cnt_rec(t_token *node)
{
	if (node == NULL)
		return (0);
	return (1 + cnt_rec(node->next));
}

void	clean_list_tokens(t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	while (token)
	{
		tmp = token->next;
		free(token->str);
		free(token);
		token = tmp;
	}
}

void	deallocate(t_cmd *curr)
{
	t_cmd	*temp;

	temp = NULL;
	if (curr == NULL)
		return ;
	while (curr)
	{
		temp = curr->next;
		clean_list_tokens(curr->tokens);
		free_2d(curr->args);
		free(curr->gpath);
		free(curr);
		curr = temp;
	}
	curr = NULL;
}

void	*get_function(char *name)
{
	(void) name;
	if (ft_compare("echo", name))
		return (execute_echo);
	if (ft_compare("pwd", name))
		return (execute_pwd);
	return (execute_default);
}

void	print_linked(t_cmd *curr)
{
	int	i;

	while (curr)
	{
		i = -1;
		token_print(curr->tokens);
		while (curr->args[++i])
			printf("Argumento: %i, %s\n", i, curr->args[i]);
		curr = curr->next;
	}
}
