#include "get_next_line.h"

void    *ft_calloc(size_t nElements, size_t sElement)
{
    int i;
    char    *pointer;

    if (nElements == 0 || sElement == 0)
    {
        nElements = 1;
        sElement = 1;
    }
    pointer = (char *)malloc(nElements * sElement);
    if (!pointer)
        return (NULL);
    i = 0;
    while (i < nElements)
    {
        pointer[i] = 0;
        i++;
    }
    return ((void *)pointer);
}

int    ft_strchr(const char *str, int c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int		ft_strlen(char *str)
{
    int	i;

    if (!str || !*str)
        return (0);
    i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *ft_strcpy(char *dest, const char *src)
{
    size_t  i;

    if (!dest || !src)
        return (NULL);
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char    *ft_strjoin(char *s1, char *s2)
{
    int s1len;
    int s2len;
    char    *new;

    s1len = ft_strlen(s1);
    s2len = ft_strlen(s2);
    new = ft_calloc(s1len + s2len + 1, sizeof(char));
    if (!new)
        return (NULL);
    new = ft_strcpy(new, s1);
    new = ft_strcpy(new + s1len, s2);
    return (new); 
}