#include "get_next_line.h"

char    *ft_reading(char *unfiltered_line, int fd, int *bytes_read)
{

    char    *read_buffer; //read buffer is where every read() command is gonna store each read
    char    *temp_buffer;

    if (!unfiltered_line)
    {
        unfiltered_line = ft_calloc(1, sizeof(char)); //in unfiltered_line is where we're gonna store an entire unfiltered line
        if (!unfiltered_line)
        {
            printf("DEBUG ERROR 1: Failed to allocate memory for unfiltered_line");
            return (NULL);
        }    
    }
    read_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!read_buffer)
    {
        printf("DEBUG ERROR 2: Read_buffer failed to allocate memory\n");
        return (NULL);
    }
    *bytes_read = 1;
    while (*bytes_read > 0 && ft_strchr(unfiltered_line, '\n') == NULL)
    {
        *bytes_read = read(fd, read_buffer, BUFFER_SIZE);
        if (*bytes_read < 0)
        {
            free(read_buffer);
            free(unfiltered_line);
            return (NULL);
        }
        if (*bytes_read == 0)
            break;
        read_buffer[*bytes_read] = '\0';
        temp_buffer = unfiltered_line;
        printf("DEBUG 1: Before ft_strjoin, this is the read_buffer string: %s\n", read_buffer);
        unfiltered_line = ft_strjoin(temp_buffer, read_buffer);
        printf("DEBUG 2: 'unfiltered_line' AFTER calling ft_strjoin: %s\n", unfiltered_line);
        free(temp_buffer);
    }
    free(read_buffer);
	return (unfiltered_line);
}

char    *ft_clean_line(char *unfiltered_line)
{
    int i;
    int j;
    char    *line;

	if (!unfiltered_line)
		return (NULL);
    i = 0;
    while (unfiltered_line[i] != '\n' && unfiltered_line[i])
        i++;
    i++;
    line = ft_calloc(i + 1, sizeof(char)); //marc f\n
    j = 0;
    while (j < i)
    {
        line[j] = unfiltered_line[j];
        j++;
    }
    line[j] = '\0';
    return (line);
}

char    *ft_save_leftovers(char *unfiltered_line)
{
    int i;
    int j;
    int line_len;
    char    *temp;

	if (!unfiltered_line)
		return (NULL);
	i = 0;
    while (unfiltered_line[i] && unfiltered_line[i] != '\n')
	{
		i++;
	}
	if (!unfiltered_line[i])
    {
        free(unfiltered_line);
		return (NULL); // in this condition here: if there's no character after incrementing i till the end, it means its on NULL character ('\0'), so it's at the end of the string. If it's at the end of the string
	//no newline, so there's no leftovers to save, we return null or the unfiltered_line without altering it
    }
    line_len = ft_strlen(unfiltered_line);
    temp = ft_calloc(line_len - i + 1, sizeof(char));
    if (!temp)
        return (NULL);
    i++;
    j = 0;
    while (i < line_len)
        temp[j++] = unfiltered_line[i++];
    free(unfiltered_line);
    temp[j] = '\0';
    return (temp);
}

char    *get_next_line(int fd)
{
    int bytes_read; //bytes or characters being read with the read() function
    char        *line; //this is the line thats gonna be returned. a clean ine
    static char *unfiltered_line; //here we gonna store the characters being read till we find a newline

    if (fd == -1 || BUFFER_SIZE <= 0)
        return (NULL);
    unfiltered_line = ft_reading(unfiltered_line, fd, &bytes_read); //unfiltered line = value returned from the reading function
	if (!unfiltered_line)
		return (NULL);
    printf("DEBUG 3: Printing unfiltered line in get_next_line right after calling ft_reading: %s\n", unfiltered_line);
    line = ft_clean_line(unfiltered_line); //split unfiltered_line and get a new buffer that ends at new line, ready to be printed
    printf("DEBUG 4 printing 'line' after calling 'ft_clean_line': %s\n", line);
    unfiltered_line = ft_save_leftovers(unfiltered_line); //manage leftovers -> update unfiltered_line to be filtered without the "line" string
    printf("DEBUG 5: printing 'unfiltered_line' right after calling ft_save_leftovers: %s\n", unfiltered_line);
	if (!line && bytes_read == 0)
        return (NULL);
    return (line);
}