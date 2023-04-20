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
        last->next = new;
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
    cmd->type = type;
    cmd->args = args;
    if (cmd->type == COMMAND)
        get_gptah(cmd);
    cmd->next = NULL;
    return (cmd);
}

void    cmd_free(t_cmd **cmd)
{
    t_cmd *tmp;

    while (*cmd)
    {
        if ((*cmd)->type == COMMAND)
            free((*cmd)->gpath);
        free_split((*cmd)->args);
        tmp = (*cmd)->next;
        free(*cmd);
        *cmd = tmp;
    }
    *cmd = NULL;
}