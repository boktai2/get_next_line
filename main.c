#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	char	*line;
	int		fd1;
	
	fd1 = open("file.txt", O_RDONLY);
	if (fd1 == -1)
	{
		printf("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd1)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("End of program.");
	close(fd1);
	return (0);
}