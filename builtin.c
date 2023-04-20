#include "minishell.h"

char    *ft_cwd(t_cmd *cmd)
{
    char *cwd;

    cwd = (char *)malloc(sizeof(char) * 1024);
    if (getcwd(cwd, 1024) != NULL)
    {
        write(cmd->fd[1], cwd, ft_strlen(cwd));
        return (cwd);
    }
    else
    {
        perror("Error on getcwd\n");
        return (NULL);
    }
}

void    ft_chdir(char *dir)
{
    char *str;

    str = str_join(ft_cwd(), dir, '/');
    if (chdir(str) != 0)
        perror("Error on chdir\n");
    free(str);
}

char    *ft_env_var(char *str)
{
    char    *new;

    new = getenv(str);
    if (new == NULL)
    {
        new = search_env_var(str);
        if (new)
        {
            
            return (new);
        }
            
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
    env_var_add_back(&mini()->env_vars, var, exp, 1);
}

void    ft_unset(char *var)
{
    remove_env_var(var, &mini()->env_vars);
}

void    init_env(char **env)
{
    int i;
    char **new;

    i = -1;
    while (env[++i])
    {
        new = str_separate(env[i]);
        env_var_add_back(&mini()->env_vars, new[0], new[1], 0);
        free(new);
    }
}