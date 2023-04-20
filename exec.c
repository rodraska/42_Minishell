#include "minishell.h"

int ft_builtin(t_cmd *cmd, char **env)
{
    if (!cmd)
        return (2);
    if (cmd->args[0][0] == 'c')
        ft_chdir(cmd->args[1]);
    else if (cmd->args[0][0] == 'e' && cmd->args[0][1] == 'c')
        ft_env_var(cmd->args[1]);
    else if (cmd->args[0][0] == 'e' && cmd->args[0][1] == 'n')
        ft_env(env);
    else if (cmd->args[0][0] == 'e' && cmd->args[0][2] == 'i')
        ft_exit();
    else if (cmd->args[0][0] == 'e' && cmd->args[0][2] == 'p')
        ft_export(cmd->args[0], cmd->args[1]);
    else if (cmd->args[0][0] == 'p')
        ft_cwd();
    else if (cmd->args[0][0] == 'u')
        ft_unset(cmd->args[0]);
    return (0);
}

int ft_exec(t_cmd *cmd, char **env)
{
    int pid;

    if(cmd_size(cmd) == 1 && cmd->type == BUILTIN)
    {
        pid = 0;
        ft_builtin(cmd, env);
        return (0);
    }
    pid = fork();
    if (pid < 0)
        return (2);
    if (pid == 0)
    {
        close(cmd->fd[0]);
        dup2(cmd->in_fd, STDIN_FILENO);
        dup2(cmd->fd[1], STDOUT_FILENO);
        close(cmd->fd[1]);
        if (cmd->type == COMMAND)
        {
            if (execve(cmd->gpath, cmd->args, env) == -1)
                perror("could not execute execve\n");
        }
        else if (cmd->type == BUILTIN)
            ft_builtin(cmd, env);
    }
    if (cmd->next)
        cmd->next->in_fd = dup(cmd->fd[0]);
    close(cmd->fd[0]);
    close(cmd->fd[1]);
    return (0);
}

int ft_cmds(t_cmd *cmds, char **env)
{
    while(cmds)
    {
        if (pipe(cmds->fd) == -1)
            return (2);
        if (cmds == cmd_last(cmds))
            cmds->fd[1] = open("outfile", O_CREAT \
			| O_TRUNC | O_RDWR, 0644);
        ft_exec(cmds, env);
        cmds = cmds->next;
    }
    return (0);
}

void    test_cmds(char **env)
{
    t_cmd *cmds;

    cmds = NULL;
    cmd_add_back(&cmds, COMMAND, ft_split("cat mini.c", ' '));
    cmd_add_back(&cmds, COMMAND, ft_split("sort", ' '));
    cmd_add_back(&cmds, COMMAND, ft_split("wc -l", ' '));
    ft_cmds(cmds, env);
    cmd_free(&cmds);
}