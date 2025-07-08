#include "get_next_line.h"

int main()
{
	int	fd;
    int i;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening the file.");
        return (1);
    }
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
}