#include "minishell.h"

void    ft_cwd(t_cmd *cmd)
{
    char *cwd;

    cwd = (char *)malloc(sizeof(char) * 1024);
    if (getcwd(cwd, 1024) != NULL)
    {
        //printf("%s\n", cwd);
        write(cmd->fd[1], cwd, ft_strlen(cwd));
    }
    else
    {
        perror("Error on getcwd\n");
        return ;
    }
}

void    ft_chdir(char *dir, t_cmd *cmd)
{
    char *str;
    char *cwd;

    cmd = NULL;
    cwd = (char *)malloc(sizeof(char) * 1024);
    getcwd(cwd, 1024);
    str = NULL;
    if (!ft_strncmp(dir, cwd, ft_strlen(cwd)))
    {
        if (chdir(dir) != 0)
            perror("Error on chdir\n");
        return ;
    }
    str = str_join(cwd, dir, '/');
    if (chdir(str) != 0)
        perror("Error on chdir\n");
    free(str);
}

void    ft_env_var(char *str, t_cmd *cmd, int f)
{
    char    *new;
    char    c;

    c = 10;
    new = getenv(str);
    if (new == NULL)
    {
        new = search_env_var(str);
        if (new)
            write(cmd->fd[1], new, ft_strlen(new));
        else
            return ;
    }
    else
        write(cmd->fd[1], new, ft_strlen(new));
        
    if (!f)
        write(cmd->fd[1], &c, 1);
    close(cmd->fd[1]);
}

void    ft_export(char *str)
{
    char **new;

    new = str_separate(str);
    env_var_add_back(&mini()->env_vars, new[0], new[1], 1);
}

void    ft_unset(char *var)
{
    remove_env_var(var, &mini()->env_vars);
}

void    ft_exit()
{  
    exit(0);
}

void    ft_env(t_cmd *cmd)
{
    char c;
    char d;

    c = 10;
    d = '=';
    while (mini()->env_vars)
    {
        write(cmd->fd[1], mini()->env_vars->var, ft_strlen(mini()->env_vars->var));
        write(cmd->fd[1], &d, 1);
        write(cmd->fd[1], mini()->env_vars->exp, ft_strlen(mini()->env_vars->exp));
        write(cmd->fd[1], &c, 1);
        mini()->env_vars = mini()->env_vars->next;
    }
    return ;
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