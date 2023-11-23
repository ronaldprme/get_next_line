/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <rprocopi@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:43:47 by rprocopi          #+#    #+#             */
/*   Updated: 2023/11/18 08:27:28 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

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
