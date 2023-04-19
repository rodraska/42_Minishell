#include "minishell.h"

void    get_paths(char **env)
{
    int i;
    char *path;
    char **paths;

    i = 0;
    path = NULL;
    while (env[i])
    {
        if (env[i][0] == 'P' && env[i][1] == 'A' \
        && env[i][2] == 'T' && env[i][3] == 'H')
        {
            path = str_trim(env[i], '=');
            break ;
        }
        i++;
    }
    paths = ft_split(path, ':');
    free(path);
    mini()->paths = paths;
}

void    get_gptah(t_cmd *cmd)
{
    char *new_path;
    int i;

    i = 0;
    while (mini()->paths[i])
    {
        new_path = path_join(mini()->paths[i], cmd->args[0]);
        if (access(new_path, F_OK) == 0)
        {
            cmd->gpath = new_path;
            return ;
        }
        free(new_path);
        i++;
    }
    cmd->gpath = NULL;
}

char    *path_join(char *s1, char *s2)
{
    int i;
    int k;
    int len1;
    int len2;
    char *new;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    new = (char *)malloc(len1 + len2 + 2);
    if (!new)
        return (NULL);
    i = -1;
    k = -1;
    while (++i < len1)
        new[i] = s1[i];
    new[i++] = '/';
    while (++k < len2)
        new[i++] = s2[k];
    new[i] = 0;
    return (new);   
}

