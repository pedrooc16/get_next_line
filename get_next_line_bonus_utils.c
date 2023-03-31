/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecosta- <pecosta-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:20:09 by pecosta-          #+#    #+#             */
/*   Updated: 2023/03/31 17:43:29 by pecosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int ft_search(char *str)
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