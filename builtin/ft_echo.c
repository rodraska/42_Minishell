/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:42 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 21:23:57 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_flag(char *str)
{
	int	j;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	j = 0;
	while (str[++j])
	{
		if (str[j] != 'n')
			return (0);
	}
	return (1);
}

int	execute_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (cmd->args[1] && check_flag(cmd->args[++i]))
			flag = 1;
	while (cmd->args[1] && cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i], 0));
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	g_terminal.status = STATUS_SUCCESS;
	return (g_terminal.status);
}

int	status(t_cmd *cmd, int status)
{
	cmd->status = status;
	return (cmd->status);
}

int	cnt(t_expo *node)
{
	if (node == NULL)
		return (0);
	return (1 + cnt(node->next));
}
