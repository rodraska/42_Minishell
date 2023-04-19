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