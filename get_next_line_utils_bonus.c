/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <rprocopi@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:43:47 by rprocopi          #+#    #+#             */
/*   Updated: 2023/11/18 09:20:39 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
