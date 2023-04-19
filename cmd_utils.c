#include "minishell.h"

int cmd_size(t_cmd *cmds)
{
    int size;

    size = 0;
    while (cmds)
    {
        size += 1;
        cmds = cmds->next;
    }
    return (size);
}

t_cmd *cmd_last(t_cmd *cmd)
{
    t_cmd *last;

    last = cmd;
    while (cmd != NULL)
    {
        last = cmd;
        cmd = cmd->next;
    }
    return (last);
}

void    cmd_add_back(t_cmd **cmds, int type, char **args)
{
    t_cmd *new;
    t_cmd *last;

    new = cmd_new(type, args);
    if (*cmds)
    {
        last = cmd_last(*cmds);
        cmds->next = new;
    }
    else
        *cmds = new;
}

t_cmd   *cmd_new(int type, char **args)
{
    t_cmd *cmd;

    cmd = (t_cmd *)malloc(sizeof(*cmd));
    if (!cmd)
        return (NULL);
    get_gptah(cmd);
    cmd->type = type;
    cmd->args = args;
    cmd->next = NULL;
    return (cmd);
}