#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t  ft_strlen(char *str)
{
    size_t  i;

    if (!str || !*str)
        return (0);
    i = 0;
    while (str[i])
        i++;
    return (i);
}

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
    while (i < (int)nElements)
    {
        pointer[i] = 0;
        i++;
    }
    return ((void *)pointer);
}

char    *ft_strcpy(char *dest, const char *src)
{
    size_t  i;

    if (!dest || !src)
	{
		return (NULL);
	}
	i = 0;
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
    ft_strcpy(new, s1);
    ft_strcpy(new + s1len, s2);
    return (new); 
}

int main()
{
    static char *unfiltered_line;
    char    *temp;
    char    *read_buffer = "1234";

    unfiltered_line = ft_calloc(1, sizeof(char));
    if (!unfiltered_line)
        return (1);
    temp = unfiltered_line;
    unfiltered_line = ft_strjoin(temp, read_buffer);
    printf("%s/n", unfiltered_line);
    free(temp);
    free(unfiltered_line);
}