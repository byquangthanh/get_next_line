/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:06:12 by sixshooterx       #+#    #+#             */
/*   Updated: 2024/02/15 14:19:21 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
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
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*temp;

	if (!line)
	{
		line = malloc(1 * sizeof(char));
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	while (!(ft_strchr(line, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(line, buffer);
		free(line);
		if (!temp)
			return (NULL);
		line = temp;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*new_remainder_position;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
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
