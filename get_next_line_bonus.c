/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecosta- <pecosta-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:42:05 by pecosta-          #+#    #+#             */
/*   Updated: 2023/03/31 17:22:35 by pecosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int	ft_search(char *str)
{
	int		i;
	int		to_found;

	i = 0;
	to_found = '\n';
	while (str[i] != to_found)
	i++;
	if (str[i] == to_found)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	unsigned long int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*newstring;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	newstring = malloc(len1 + len2 + 1);
	if (!newstring)
		return (NULL);
	ft_strcpy(newstring, s1);
	ft_strcpy(newstring + len1, s2);
	free(s1);
	return (newstring);
}

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
		if (!(ft_search(buffer[fd])))
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