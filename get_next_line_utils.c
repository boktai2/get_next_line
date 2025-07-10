/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcfer3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:58:06 by marcfer3          #+#    #+#             */
/*   Updated: 2025/07/10 17:58:10 by marcfer3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_all(char	*read_buffer, char *unfiltered_line)
{
	free(read_buffer);
	read_buffer = NULL;
	free(unfiltered_line);
	unfiltered_line = NULL;
	return (NULL);
}

void	*ft_calloc(size_t nElements, size_t sElement)
{
	int		i;
	char	*pointer;

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

char	*ft_strchr(char *str, int c)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	if (str[i] == (char)c)
		return ((char *)str + i);
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

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

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1len;
	int		s2len;
	char	*new;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	new = ft_calloc(s1len + s2len + 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcpy(new + s1len, s2);
	return (new);
}
