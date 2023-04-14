#include "minishell.h"

char    *ft_cwd()
{
    char *cwd;

    cwd = (char *)malloc(sizeof(char) * 1024);
    if (getcwd(cwd, 1024) != NULL)
        return (cwd);
    else
    {
        perror("Error on getcwd\n");
        return (NULL);
    }
}

void    ft_chdir(char *dir)
{
    if (chdir(str_join(ft_cwd(), dir)) != 0)
        perror("Error on chdir\n");
}

char    *ft_env_var(char *str)
{
    char    *new;

    new = getenv(str);
    if (new == NULL)
    {
        new = search_env_var(str);
        if (new)
            return (new);
        else
        {
            perror("error env variable\n");
            return (NULL);
        }
    }
    else
        return (new);
}

void    ft_export(char *var, char *exp)
{
    env_var_add_back(&mini()->env_vars, var, exp);
}

void    ft_unset(char *var)
{
    remove_env_var(var);
}