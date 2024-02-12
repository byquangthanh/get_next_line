/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sixshooterx <sixshooterx@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:06:12 by sixshooterx       #+#    #+#             */
/*   Updated: 2024/02/12 13:13:33 by sixshooterx      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*read_from_file(int fd, char *line)
{
	char	*buffer;
	int		bytes_read;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	while (!(ft_strchr(line, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			return (NULL);
		}
		line = ft_strjoin(line, buffer);
	}
	return (line);
}

char	*ensure_remainder_initialized(char *remainder)
{
	if (!remainder)
		remainder = ft_calloc(1, sizeof(char));
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*new_remainder_position;
	char		*temp;

	line = NULL;
	remainder = ensure_remainder_initialized(remainder);
	remainder = read_from_file(fd, remainder);
	if (!remainder)
		return (NULL);
	line = split_next_line(remainder);
	new_remainder_position = ft_strchr(remainder, '\n');
	if (new_remainder_position)
	{
		temp = ft_strdup(new_remainder_position + 1);
		free(remainder);
		remainder = temp;
	}
	else
	{
		free(remainder);
		remainder = NULL;
	}
	return (line);
}


int	main(void)
{
	int  fd;
	char *line;
	int  count;

	count = 0;
	fd = open("example.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count++;
		printf("[%d]:%s\n", count, line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}
