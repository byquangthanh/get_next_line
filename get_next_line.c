/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sixshooterx <sixshooterx@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:06:12 by sixshooterx       #+#    #+#             */
/*   Updated: 2024/02/08 10:48:06 by sixshooterx      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char *get_next_line(int fd) {
	static char	*remainder = NULL; // Holds data across calls.
	char		*line = NULL; // The next line to return.
	char		*new_remainder_position; // Position after the newline to start the next remainder.
	char		*temp; // Temporary pointer for operations.

	if (!remainder)
		remainder = ft_calloc(1, sizeof(char)); // Ensure initialized.

	// Read and accumulate content into 'remainder'.
	remainder = read_from_file(fd, remainder);

	// If read_from_file returns NULL, either an error occurred, or we reached EOF without any data.
	if (!remainder)
		return NULL; // Nothing more to read or an error happened.

	// Use split_next_line to get the next line from remainder.
	line = split_next_line(remainder);

	// Find the position of the newline character in the remainder.
	new_remainder_position = ft_strchr(remainder, '\n');

	// Prepare the remainder for the next call.
	if (new_remainder_position) {
		temp = ft_strdup(new_remainder_position + 1); // Create a new remainder starting after the newline.
		free(remainder); // Free the old remainder.
		remainder = temp; // Update the static remainder.
	} else {
		free(remainder); // If there's no newline, we've processed all content.
		remainder = NULL;
	}

	return line; // Return the extracted line.
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
