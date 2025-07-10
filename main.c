#include "get_next_line.h"

int main()
{
    int fd;
    char    *line;

    fd = open("tests/big_line_no_nl", O_RDONLY);
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
