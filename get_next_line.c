/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecosta- <pecosta-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:02:41 by pecosta-          #+#    #+#             */
/*   Updated: 2023/03/27 16:07:41 by pecosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#define BUFFER_SIZE 40
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char	*ft_search(const char *s, int c)
{
	unsigned char	i;

	i = c;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)i)
			return ((char *)s);
		s++;
	}
	if (i == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	unsigned long int	i;
	
	if (!s)
		return (0);
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

	if (*buffer == 0)
	{
		free(buffer);
		return (NULL);
	}
	size_of_buffer = ft_strlen(buffer) - i;
	refresh = malloc(sizeof(char) * (size_of_buffer + 1));  //nesteeeeee
	if (!refresh)
		return (NULL);
	if (buffer[i] == '\n')
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
	char	temp[BUFFER_SIZE + 1];

	while ((bytes = read(fd,temp,BUFFER_SIZE)) > 0)
	{
		temp[bytes] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (ft_search(buffer, '\n') || bytes == 0)
		break;
	}
    if (bytes < 0)
	{
		if (buffer)
		{
			free(buffer);  
		}
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	char 	*line;
	static char *buffer;
	int	i;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	if (buffer && (ft_search(buffer, '\n')))
		i = 1;
	if (!i)
	{
		buffer = read_line(fd, buffer);
	if (!buffer)
			return (NULL);
	}
	i = 0;
	line = get_the_next_line(buffer, &i);
	buffer = refresh_buffer(buffer, i);
	return (line);
	}


int main()
{
	char *line;
	int fd = open("texto.txt", O_RDONLY);
        line = get_next_line(fd);
		int i = 0;
	while (i < 2)
	{
		printf("%s", line);
		free(line);
		i++;
        line = get_next_line(fd);
	}
	free(line);
	line = get_next_line(55);
	free(line);
        //printf("\n");
		while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		if (!line)
		break;
	}
	free(line);
	}