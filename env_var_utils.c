#include "minishell.h"

void    env_var_add_back(t_env_var **lst, char *var, char *exp)
{
    t_env_var *new;
    t_env_var *last;

    new = env_var_new(var, exp);
    if (*lst)
    {
        last = env_var_last(*lst);
        last->next = new;
    }
    else
        *lst = new;
}

t_env_var   *env_var_new(char *var, char *exp)
{
    t_env_var *elem;

    elem = (t_env_var *)malloc(sizeof(*elem));
    if (!elem)
        return (NULL);
    elem->var = var;
    elem->exp = exp;
    elem->next = NULL;
    return (elem);
}

t_env_var   *env_var_last(t_env_var *lst)
{
    printf("last\n");
    t_env_var *last;

    last = lst;
    while (lst != NULL)
    {
        last = lst;
        lst = lst->next;
    }
    return (last);
}

void    env_var_print(t_env_var *lst)
{
    while (lst)
    {
        printf("var: %s exp: %s\n", lst->var, lst->exp);
        lst = lst->next;
    }
}

void    env_var_free(t_env_var **lst)
{
    t_env_var *tmp;

    while (*lst)
    {
        tmp = (*lst)->next;
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}