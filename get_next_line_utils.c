#include "get_next_line.h"

void    *ft_calloc(size_t nElements, size_t sElement)
{
    size_t i;
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
    while (i < nElements * sElement) //nelements * size_of_elements because i want to 0 all the bytes
    {
        pointer[i] = 0;
        i++;
    }
    return ((void *)pointer);
}

/*char    *ft_strchr(const char *str, int c)
{
    int i;

    if (c == '\0')
        return (NULL);
    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return ((char *)str + i);
        i++;
    }
    return (NULL);
}*/

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != '\0')
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	if (*ptr == (unsigned char)c)
		return (ptr);
	return (NULL);
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