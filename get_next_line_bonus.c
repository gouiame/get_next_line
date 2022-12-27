/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:06:01 by cgouiame          #+#    #+#             */
/*   Updated: 2022/12/25 19:34:44 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *p, char *buffer)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (p == NULL)
		p = ft_strdup("");
	result = (char *)malloc (ft_strlen (p) + ft_strlen (buffer) + 1);
	if (buffer == (NULL))
		return (NULL);
	while (p[i] != '\0')
	{
		result[i] = p[i];
		i++;
	}
	while (buffer[j] != '\0')
		result[i++] = buffer[j++];
	result[ft_strlen(p) + ft_strlen(buffer)] = '\0';
	free(p);
	return (result);
}

int	ft_newline(char *p)
{
	int	i;

	i = 0;
	if (p == NULL)
		return (0);
	while (p[i] != '\0')
	{
		if (p[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*result;
	static char	*p[OPEN_MAX];
	int			x;

	x = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof (char));
	if (buffer == NULL)
		return (NULL);
	while (ft_strchr(p[fd], '\n') == 0 && x > 0)
	{
		x = read (fd, buffer, BUFFER_SIZE);
		if (x == -1)
			return (free(p[fd]), free(buffer), NULL);
		buffer[x] = '\0';
		p[fd] = ft_strjoin(p[fd], buffer);
	}
	free (buffer);
	result = ft_substr(p[fd], 0, ft_newline(p[fd]) + 1);
	p[fd] = ft_after_newline(p[fd]);
	return (result);
}
