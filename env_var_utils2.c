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

/* void    remove_env_var(char *var, t_env_var **lst)
{
    t_env_var *prev;
    t_env_var *tmp;

    prev = NULL;
    head = lst;
    while (*lst && ft_strcmp((*lst)->var, var) != 0)
    {
        prev = *lst;
        (*lst) = (*lst)->next;
    }
    if (*lst == NULL)
        return ;
    if (prev == NULL)
    {
        tmp = (*lst)->next;
        free(*lst);
        *lst = tmp;     
    }
    else
    {
        prev->next = (*lst)->next;
        free(*lst);
    }
} */

void    remove_env_var(char *var, t_env_var **lst)
{
    t_env_var *curr;
    t_env_var *prev;

    curr = *lst;
    prev = NULL;
    while (curr != NULL)
    {
        if (ft_strcmp(curr->var, var) == 0)
        {
            if (prev == NULL)
                *lst = curr->next;
            else
                prev->next = curr->next;
            free(curr);
        }
        prev = curr;
        curr = curr->next; 
    }
}
