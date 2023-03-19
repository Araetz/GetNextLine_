
#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>
#include "stdlib.h"

static char	*ft_read_line(char *stash)
{
	int		size;
	char	*s;

	size = 0;
	if (!stash || !stash[size])
		return (NULL);
	while (stash[size] && stash[size] != '\n')
		size++;
	if (stash[size] =='\n')
		size ++;
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	size = 0;
	while (stash[size] && stash[size] != '\n')
	{
		s[size] = stash[size];
		size++;
	}
	if (stash[size] == '\n')
	{
		s[size] = stash[size];
		size++;
	}
	s[size] = '\0';
	return (s);
}

static char	*ft_save_stash(char *stash)
{
	int		size;
	int		i;
	char	*s;

	size = 0;
	while (stash[size] && stash[size] != '\n')
		size++;
	if (!stash[size])
	{
		free(stash);
		return (NULL);
	}
	s = ft_calloc(sizeof(char), (ft_strlen(stash) - size + 1));
	if (!s)
		return (NULL);
	size++;
	i = 0;
	while (stash[size])
		s[i++] = stash[size++];
	s[i] = '\0';
	free(stash);
	return (s);
}

static char	*ft_read_buffer(int fd, char *stash)
{
	char	*buff;
	int		bytes_readed;

	buff = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_readed = 1;
	while (!ft_strchr(stash, '\n') && bytes_readed != 0)
	{
		bytes_readed = read(fd, buff, BUFFER_SIZE);
		if (bytes_readed < 0)
		{
			free(stash);
			free(buff);
			return (NULL);
		}
		buff[bytes_readed] = '\0';
		stash = ft_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*next_line;

	if  (fd < 0 || BUFFER_SIZE <= 0 || read(fd,0,0) < 0){
		
		if (!next_line)
			return (NULL);
		free(next_line);
		next_line = NULL; 
		return (NULL);
		}
	next_line = ft_read_buffer(fd, next_line);	
	
	line = ft_read_line(next_line);
	next_line = ft_save_stash(next_line);
	return (line);
}
/*
void seeleaks()
{
	system("leaks -q a.out");
}

int main()
{
    int fd;
	char *str;
	int count;
   
	atexit(&seeleaks);
    fd = open("archivo.txt", O_RDONLY);
	count = 0;
    while(count < 5)
    {
        str = get_next_line(fd);
		printf("%s", str);
        free(str);
		count++;
    }
	close(fd);
}
*/