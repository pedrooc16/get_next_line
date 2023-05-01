/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecosta- <pecosta-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:42:05 by pecosta-          #+#    #+#             */
/*   Updated: 2023/05/01 14:15:55 by pecosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_the_next_line(char *buffer, int * i)
{
	char 	*line;
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
	line = malloc(sizeof(char) * (*(i) + 2));
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

char	*refresh_buffer(char *buffer, int i)
{
	char 	*refresh;
	size_t	size_of_buffer;
	int	j;

	if (buffer[i] == 0)
	{
		free(buffer);
		return (NULL);
	}
	size_of_buffer = ft_strlen(buffer) - i;
	refresh = malloc(sizeof(char) * (size_of_buffer + 1));  
	if (!refresh)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
	refresh[j++] = buffer[i++];
	refresh[j] = '\0';
	free(buffer);
	return(refresh);
}

char	*read_line(int fd, char *buffer)
{
	int		bytes;
	char	*temp;
	
	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while ((bytes = read(fd,temp,BUFFER_SIZE)) > 0)
	{
		temp[bytes] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (ft_search(buffer, '\n'))
		break;
	}
    if (bytes < 0)
	{
		if (buffer && (ft_search(buffer, '\0')))
				free(buffer);
		free(temp); 
		return (NULL);
	}
	free(temp);
	return(buffer);
	}

/*
buffer has size of 1024 because linux systems limit
the number of file descriptors that any
one process may open to 1024 per process.
*/

char	*get_next_line(int fd)
{
	char 	*line;
	static char *buffer[1024];
	int	i;
	
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	if (buffer[fd] && (ft_search(buffer[fd], '\n')))
		i = 1;
	if (!i)
	{
		buffer[fd] = read_line(fd, buffer[fd]);
			if (!buffer[fd])
		return (NULL);
	}
	i = 0;
	line = get_the_next_line(buffer[fd], &i);
	buffer[fd] = refresh_buffer(buffer[fd], i);
	return (line);
	}


	/*int main(void)
{
	int fd;
	int fd2;
	char *line;

	fd = open("texto.txt", O_RDONLY);
	fd2 = open("joao.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("line 1 is %s", line);
	free(line);
	line = get_next_line(fd);
	printf("line 1 is %s", line);
	free(line);
	line = get_next_line(fd2);
	printf("line 1 is %s", line);
	free(line);
	line = get_next_line(fd2);
	printf("line 1 is %s", line);
	free(line);
	close(fd);
	close (fd2);
	return (0);
}*/