/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <rprocopi@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:43:47 by rprocopi          #+#    #+#             */
/*   Updated: 2023/11/18 08:27:13 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];

	line = NULL;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		ft_clean_buffer(buffer);
		return (NULL);
	}
	while (*buffer != 0 || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = ft_strjoinm(line, buffer);
		if (ft_check_newline(buffer))
			break ;
	}
	return (line);
}

int main(void)
{
    int fd;
 	char *line;
 	int i;

 	i = 1;
 	fd = open("file", O_RDONLY);
 	if (fd < 0)
 	{
 		perror("Error opening file");
 		return 1;
 	}

 	while ((line = get_next_line(fd)) != NULL)
 	{
 		printf("Line %d:\n", i++);
 		if (line[0] != '\0') // Check if line is not empty
 			printf("-> %s", line);
		else
 			printf("-> [Empty Line]");
 		free(line);
 	}

 	close(fd);
 	return 0;
 }
