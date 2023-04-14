#include "minishell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *str_join(char *old, char *seg)
{
    int old_len;
    int seg_len;
    int i;
    int j;
    char    *new;

    old_len = ft_strlen(old);
    seg_len = ft_strlen(seg);
    new = (char *)malloc(old_len + seg_len + 2);
    i = -1;
    while (++i < old_len)
        new[i] = old[i];
    new[i++] = '/';
    j = -1;
    while (++j < seg_len)
        new[i++] = seg[j];
    new[i] = 0;
    return (new);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return (0);
}

void    free_split(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
    return ;
}

t_mini  *mini(void)
{
    static t_mini mini;

    return (&mini);
}