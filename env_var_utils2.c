#include "minishell.h"

char    *search_env_var(char *var)
{
    t_env_var *env_vars;

    env_vars = mini()->env_vars;
    while (env_vars)
    {
        if(!ft_strcmp(env_vars->var, var))
            return (env_vars->exp);
        env_vars = env_vars->next;
    }
    return (NULL);
}

void    remove_env_var(char *var)
{
    t_env_var *curr;
    t_env_var *prev;

    curr = mini()->env_vars;
    prev = NULL;
    while (curr && ft_strcmp(curr->var, var) != 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL)
        return ;
    if (prev == NULL)
        mini()->env_vars = curr->next;
    else
        prev->next = curr->next;
    free(curr);

}