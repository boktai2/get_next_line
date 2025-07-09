#include "get_next_line.h"

char    *ft_reading(char *unfiltered_line, int fd, int *bytes_read)
{

    char    *read_buffer; //read buffer is where every read() command is gonna store each read
    char    *temp_buffer;

    if (!unfiltered_line)
    {
        unfiltered_line = ft_calloc(1, sizeof(char)); //in unfiltered_line is where we're gonna store an entire unfiltered line
        if (!unfiltered_line)
        return (NULL);
    }
    read_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!read_buffer)
        return (NULL);
    *bytes_read = 1;
    while (*bytes_read > 0 && !ft_strchr(unfiltered_line, '\n'))
    {
        *bytes_read = read(fd, read_buffer, BUFFER_SIZE);
        if (*bytes_read == -1)
        {
            free(read_buffer);
            free(unfiltered_line);
            return (NULL);
        }
        if (*bytes_read == 0)
            break;
        read_buffer[*bytes_read] = '\0';
        //printf("DEBUG 1: 'read_buffer string after reading: %s\n", read_buffer);
        temp_buffer = unfiltered_line;
        unfiltered_line = ft_strjoin(temp_buffer, read_buffer);
        //printf("DEBUG 2: unfiltered_line after strjoin with the read_buffer: %s\n", unfiltered_line);
        free(temp_buffer);
    }
    free(read_buffer);
    return (unfiltered_line);
}

char    *ft_clean_line(char *unfiltered_line)
{
    int i;
    char    *line;

    i = 0;
    while (unfiltered_line[i] != '\n' && unfiltered_line[i])//mueve i hasta \n 
        i++;
    line = ft_calloc(i + 1 + 1, sizeof(char));// i + 1(\n) + 1('\0)
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

char    *ft_save_leftovers(char *unfiltered_line)
{
    int i;
    int j;
    int line_len;
    char    *temp;

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
    {
        temp[j] = unfiltered_line[i];
        j++;
        i++;
    }
    free(unfiltered_line);
    return (temp);
}

char    *get_next_line(int fd)
{
    int bytes_read;
    char    *line;
    static char *unfiltered_line;

    if (fd == -1)
        return (NULL);
    unfiltered_line = ft_reading(unfiltered_line, fd, &bytes_read);
    //printf("DEBUG 3: unfiltered_line received from ft_reading: %s\n",unfiltered_line);
    if (!unfiltered_line || !*unfiltered_line)
    {
        free(unfiltered_line);
        return (NULL);
    }
    line = ft_clean_line(unfiltered_line);
    //printf("DEBUG 4: line after ft_clean_line: %s\n", line);
    unfiltered_line = ft_save_leftovers(unfiltered_line);
    //printf("DEBUG 5: unfiltered_line after deleting 'line' from it, leaving only the leftovers: %s\n", unfiltered_line);
    return (line);
}