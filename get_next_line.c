/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecosta- <pecosta-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:18:26 by pecosta-          #+#    #+#             */
/*   Updated: 2023/03/08 16:18:26 by pecosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>

char	*file_to_read(int fd, char *buffer)
{
	int		i;
	char 	temp[BUFFER_SIZE + 1];
	int		bytes;

	i = 0;
	while ((bytes = read(fd,temp,BUFFER_SIZE)) > 0)
	{
		temp[bytes] = '\0';
		buffer = ft_strjoin(buffer, temp);
		while(buffer[i])
		{
			if (buffer[i] == '\n')
			break;
			i++;
		}
	}
	if (bytes == -1)
		return (NULL);
	return (buffer);
}

char	*get_the_next_line(char *buffer)
{
	char *line;
	int		i;
	int		j;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	
	while (buffer[j] != '\n')
	{
	line[j] = buffer[j];
	j++;
	}
	if (buffer[j] == '\n')
	line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	char *line;
	static char *buffer;

	buffer = file_to_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_the_next_line(buffer);
	return (line);
}

int main()
{
	char *line;
	int fd = open("texto.txt", O_RDONLY);
        line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
                line = get_next_line(fd);
	}
        printf("\n");
}