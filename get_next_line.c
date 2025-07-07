#include "get_next_line.h"

char    *ft_reading(char *unfiltered_line, int fd, int *bytes_read)
{

    char    *read_buffer; //read buffer is where every read() command is gonna store each read

    if (!unfiltered_line)
    {
        unfiltered_line = ft_calloc(1, sizeof(char)); //in unfiltered_line is where we're gonna store an entire unfiltered line
        if (!unfiltered_line)
        return (NULL);
    }
    read_buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
    *bytes_read = 1;
    while (*bytes_read > 0 || !ft_strchr(unfiltered_line, '\n'))
    {
        *bytes_read = read(fd, read_buffer, BUFFER_SIZE);
        if (*bytes_read == -1)
        {
            free(read_buffer);
            free(unfiltered_line);
            return (NULL);
        }
        read_buffer[*bytes_read] = '\0';
        unfiltered_line = ft_strjoin(unfiltered_line, read_buffer);
        return (unfiltered_line);
    }
    
}

char    *ft_clean_line(char *unfiltered_line)
{
    int i;
    int j;
    char    *line;

    i = 0;
    while (unfiltered_line[i] != '\n')
        i++;
    i++;
    line = ft_calloc(i + 1, sizeof(char));
    j = 0;
    while (j <= i)
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

    while (unfiltered_line[i] != '\n')
        i++;
    i++;
    line_len = ft_strlen(unfiltered_line);
    temp = ft_calloc(line_len - i, sizeof(char));
    j = 0;
    while (i <= line_len)
    {
        temp[j] = unfiltered_line[i];
        j++;
        i++;
    }
    free(unfiltered_line);
    temp[j] = '\0';
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
    line = ft_clean_line(unfiltered_line);
    unfiltered_line = ft_save_leftovers(unfiltered_line);
}