#include "get_next_line.h"

int main()
{
    int fd;
    char    *line;

    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening the file.");
        return (1);
    }
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    close(fd);
    return (0);
}