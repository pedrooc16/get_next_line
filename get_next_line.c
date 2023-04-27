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

#include "get_next_line.h"

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


/*int main()
{
	char *line;
	int fd = open("joao.txt", O_RDONLY);
        line = get_next_line(fd);
		while (line)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}
		free(line);
}*/