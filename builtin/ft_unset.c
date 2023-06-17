/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:49:48 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 21:24:12 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**destroy_row(char **env, char *str)
{
	char	**new;
	int		i;
	int		i_c;
	int		k;

	new = malloc_ob(sizeof(char *) * (ft_strlen_2d(env) + 1));
	i = 0;
	i_c = 0;
	k = ft_strlen_2d(env);
	while (i_c < k && env[i])
	{
		if (!(ft_strncmp(env[i], str, ft_strlen(env[i], '=')) \
		== 0 && ft_strlen(str, 0) == ft_strlen(env[i], '=')))
		{
			new[i_c] = ft_strdup(env[i]);
			i_c++;
			i++;
		}
		else
			i++;
	}
	free_2d(env);
	return (new);
}

void	destroy_first_node(t_expo **list)
{
	t_expo	*tmp;

	tmp = (*list);
	(*list) = (*list)->next;
	free(tmp);
	free(tmp->variable);
	free(tmp->value);
	tmp = NULL;
}

void	destroy_node_2(char *str, t_expo *tmp, t_expo *aux)
{
	while (tmp->next)
	{
		if (ft_strncmp(tmp->next->variable, str, ft_strlen(tmp->next->variable, \
		'=')) == 0 && ft_strlen(str, 0) == ft_strlen(tmp->next->variable, '='))
		{
			aux = tmp->next;
			if (tmp->next)
				tmp->next = tmp->next->next;
			free(aux->variable);
			free(aux->value);
			free(aux);
			tmp = NULL;
			return ;
		}
		else
			tmp = tmp->next;
	}
}

void	destroy_node(t_expo **list, char *str, t_expo *tmp, t_expo *aux)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen((*list)->variable, '=');
	if (ft_strncmp((*list)->variable, str, ft_strlen((*list)->variable, '='\
	)) == 0 && ft_strlen(str, 0) == ft_strlen((*list)->variable, '='))
	{
		destroy_first_node(list);
		return ;
	}
	destroy_node_2(str, tmp, aux);
}

int	execute_unset(t_cmd *cmd)
{
	int		len_variable;
	int		i;
	t_expo	*tmp;

	i = 1;
	tmp = g_terminal.expo;
	len_variable = 0;
	while (tmp && cmd->args[i])
	{
		if (ft_strncmp(tmp->variable, cmd->args[i], ft_strlen(tmp->variable, '='\
		)) == 0 && ft_strlen(cmd->args[i], 0) == ft_strlen(tmp->variable, '='))
		{
			g_terminal.env = destroy_row(g_terminal.env, cmd->args[i]);
			destroy_node(&g_terminal.expo, cmd->args[i], g_terminal.expo, NULL);
			if (cmd->args[i + 1] && ++i)
				tmp = g_terminal.expo;
			else
				break ;
			tmp = g_terminal.expo;
		}
		tmp = tmp->next;
	}
	g_terminal.status = STATUS_SUCCESS;
	return (g_terminal.status);
}
