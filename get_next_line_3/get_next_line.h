#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
# endif

int main(void);
char    *get_next_line(int fd);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_strcpy(char *dest, const char *src);
size_t  ft_strlen(char *str);
char    *ft_strchr(char *str, int c);
void    *ft_calloc(size_t nElements, size_t sElement);

# endif
