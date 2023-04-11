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
        perror("error env variable\n");
        return (NULL);
    }
    else
        return (new);
}