#include "minishell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char    *str_join(char *old, char *seg, char c)
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
    new[i++] = c;
    j = -1;
    while (++j < seg_len)
        new[i++] = seg[j];
    new[i] = 0;
    if (old)
        free(old);
    return (new);
}

char    **str_separate(char *str)
{
    char    **new;
    char    *var;
    char    *exp;
    int     i;
    int     j;

    new = (char **)malloc(sizeof(char *) * 2);
    i = 0;
    while (str[i] != '=')
        i++;
    var = (char *)malloc(i + 1);
    exp = (char *)malloc(ft_strlen(str) - i);
    i = -1;
    while (str[++i] != '=')
        var[i] = str[i];
    var[i++] = 0;
    j = -1;
    while (str[++i])
        exp[++j] = str[i];
    exp[++j] = 0;
    new[0] = var;
    new[1] = exp;
    return (new);
}

char    *str_trim(char *src, char c)
{
    char *dest;
    int  len;
    int  i;
    int  j;

    j = 0;
    while (src[j] != c)
        j++;
    j++;
    len = ft_strlen(src) - j;
    dest = (char *)malloc(len + 1);
    i = 0;
    while (i < len)
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = 0;
    return (dest);
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