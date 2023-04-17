/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecosta- <pecosta-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:42:05 by pecosta-          #+#    #+#             */
/*   Updated: 2023/04/02 14:16:07 by pecosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_the_next_line(char *buffer, int * i)
{
	char *line;
	int		j;
	int		index;

	index = 0;
	if (buffer[index] == 0)
		return (NULL);
	while (buffer[index] && buffer[index] != '\n')
	{
		index++;
		(*i)++;
	}
	line = malloc(sizeof(char) * (index + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (buffer[j] && buffer[j] != '\n')
	{
		line[j] = buffer[j];
		j++;
	}
	if (buffer[j] == '\n')
	line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*refresh_buffer(char *buffer, int * i)
{
	int		index;
	char 	*refresh;
	size_t	size_of_buffer;
	int	j;

	if (*buffer == 0)
	{
		free(buffer);
		return (0);
	}
	index = *i;
	size_of_buffer = ft_strlen(buffer) - index;
	refresh = malloc(sizeof(char) * (size_of_buffer + 1));

	if (!refresh)
		return (NULL);
	if (buffer[index] == '\n')
	index++;
	j = 0;
	while (buffer[index])
	refresh[j++] = buffer[index++];
	refresh[j] = '\0';
	free(buffer);
	return(refresh);
}

char	*get_next_line(int fd)
{
	char 	*line;
	static char *buffer[FOPEN_MAX];
	int	i;
	char	temp[BUFFER_SIZE + 1];
	int		bytes;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	while ((bytes = read(fd,temp,BUFFER_SIZE)) > 0)
	{
		temp[bytes] = '\0';
		buffer[fd] = ft_strjoin(buffer[fd], temp);
		if ft_search(buffer[fd])
		break;
	}
	if ((bytes == -1) || (!buffer[fd]))
		return (NULL);
	i = 0;
	line = get_the_next_line(buffer[fd], &i);
	buffer[fd] = refresh_buffer (buffer[fd], &i);
	return (line);
}

int main(void)
{
	int fd;
	int fd2;

	fd = open("texto.txt", O_RDONLY);
	fd2 = open("joao.txt", O_RDONLY);
	printf("line 01: %s\n", get_next_line(fd));
	printf("line 02: %s\n", get_next_line(fd));
	printf("line 01: %s\n", get_next_line(fd2));
	printf("line 02: %s\n", get_next_line(fd2));
	printf("line 01: %s\n", get_next_line(fd));
	printf("line 02: %s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	close(fd);
	close (fd2);
	return (0);
}