#include "get_next_line.h"

int main()
{
    int fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening the file.");
        return (1);
    }
    while (((line = get_next_line(fd)) != NULL))
    {
        printf("%s", line);
        free(line);
    }
    if (line)
        free(line);
    close(fd);
    return (0);
}