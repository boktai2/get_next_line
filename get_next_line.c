/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcfer3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:40:52 by marcfer3          #+#    #+#             */
/*   Updated: 2025/07/10 16:41:58 by marcfer3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_init(char *unfiltered_line)
{
	unfiltered_line = ft_calloc(1, sizeof(char));
	if (!unfiltered_line)
		return (NULL);
	return (unfiltered_line);
}

char	*ft_reading(char *unfiltered_line, int fd, int *bytes_read)
{
	char	*read_buffer;
	char	*temp_buffer;

	if (!unfiltered_line)
		unfiltered_line = line_init(unfiltered_line);
	if (ft_strchr(unfiltered_line, '\n'))
		return (unfiltered_line);
	read_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buffer)
		return (NULL);
	*bytes_read = 1;
	while (*bytes_read > 0)
	{
		*bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
			return (free_all(read_buffer, unfiltered_line));
		if (*bytes_read == 0)
			break ;
		read_buffer[*bytes_read] = '\0';
		temp_buffer = unfiltered_line;
		unfiltered_line = ft_strjoin(temp_buffer, read_buffer);
		free(temp_buffer);
		if (!unfiltered_line)
			return (free(read_buffer), NULL);
		if (ft_strchr(read_buffer, '\n'))
			break ;
	}
	free(read_buffer);
	return (unfiltered_line);
}

char	*ft_clean_line(char *unfiltered_line)
{
	int		i;
	char	*line;

	i = 0;
	while (unfiltered_line[i] != '\n' && unfiltered_line[i])
		i++;
	line = ft_calloc(i + 1 + 1, sizeof(char));
	i = 0;
	while (unfiltered_line[i] && unfiltered_line[i] != '\n')
	{
		line[i] = unfiltered_line[i];
		i++;
	}
	line[i] = unfiltered_line[i];
	i++;
	line[i] = '\0';
	return (line);
}

char	*ft_save_leftovers(char *unfiltered_line)
{
	int		i;
	int		j;
	int		line_len;
	char	*temp;

	i = 0;
	while (unfiltered_line[i] != '\n' && unfiltered_line[i])
		i++;
	if (unfiltered_line[i] == '\0')
	{
		free(unfiltered_line);
		return (NULL);
	}
	i++;
	line_len = (int)ft_strlen(unfiltered_line);
	temp = ft_calloc(line_len - i + 1, sizeof(char));
	j = 0;
	while (i <= line_len)
		temp[j++] = unfiltered_line[i++];
	free(unfiltered_line);
	return (temp);
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	static char	*unfiltered_line;
	char		*line;

	if (fd == -1)
		return (NULL);
	unfiltered_line = ft_reading(unfiltered_line, fd, &bytes_read);
	if (!unfiltered_line || !*unfiltered_line)
	{
		free(unfiltered_line);
		return (NULL);
	}
	line = ft_clean_line(unfiltered_line);
	unfiltered_line = ft_save_leftovers(unfiltered_line);
	return (line);
}
