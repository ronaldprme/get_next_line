#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i + (str[i] == '\n'));
}

void	ft_clean_buffer(int fd, char **buffer)
{
	int	i;

	i = 0;
	while (buffer[fd][i])
		buffer[fd][i++] = 0;
}

int	ft_check_newline(char *buffer)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 0;
	j = 0;
	while (buffer[i])
	{
		if (flag)
		{
			buffer[j] = buffer[i];
			j++;
		}
		if (buffer[i] == '\n')
			flag = 1;
		buffer[i] = '\0';
		i++;
	}
	return (flag);
}

char	*ft_strjoinm(char *s1, char *s2)
{
	char	*s3;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (size + 1));
	if (!s3)
		return (NULL);
	while (s1 && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		s3[i++] = s2[j++];
		if (s2[j - 1] == '\n')
			break ;
	}
	s3[i] = '\0';
	free(s1);
	return (s3);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];

	line = NULL;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
	{
		ft_clean_buffer(fd, (char **)buffer);
		return (NULL);
	}
	while (buffer[fd][0] != 0 || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		line = ft_strjoinm(line, (char *)buffer[fd]);
		if (ft_check_newline((char *)buffer[fd]))
			break ;
	}
	return (line);
}

int	main(int av, char **ac)
{
	int		fd[av - 1];
	char	*line[av - 1];
	int		i;
    int     nfiles;

    if (av < 2)
        printf("infomre pelo menos um arquivo");
    nfiles = av - 1;
	i = 0;
    while (i < nfiles)
    {
        fd[i] = open(ac[i + 1], O_RDONLY);
        if (fd[i] < 0)
            perror("Error opening file");
        while ((line[i] = get_next_line(fd[i])) != NULL)
        {
            printf("Line %d:\n", i);
            if (line[i] != (void *)0) // Check if line is not empty
                printf("-> %s", line[i]);
            else
                printf("-> [Empty Line]");
            free(line[i]);
        }
        close(fd[i]);
        i++;
	}
	return 0;
}