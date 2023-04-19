#include "minishell.h"

int ft_builtin(t_cmd *cmd)
{
    if (!cmd)
        return (2);
    return (0);
}

int ft_exec(t_cmd *cmd, char **env)
{
    int pid;

    if(cmd_size(cmd) == 1 && cmd->type == BUILTIN)
    {
        pid = 0;
        ft_builtin(cmd);
        return (0);
    }
    pid = fork();
    if (pid < 0)
        return (2);
    if (pid == 0)
    {
        if (cmd->type == COMMAND)
        {
            if (execve(cmd->gpath, cmd->args, env) == -1)
                perror("could not execute execve\n");
        }
        else if (cmd->type == BUILTIN)
            ft_builtin(cmd);
    }
    return (0);
}

int ft_cmds(t_cmd *cmds, char **env)
{
    while(cmds)
    {
        if (pipe(cmds->fd) == -1)
            return (2);
        ft_exec(cmds, env);
        cmds = cmds->next;
    }
    return (0);
}