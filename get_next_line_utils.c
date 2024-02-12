/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sixshooterx <sixshooterx@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:32:00 by sixshooterx       #+#    #+#             */
/*   Updated: 2024/02/12 12:58:32 by sixshooterx      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*temp_ptr;
	size_t	i;
	size_t	total_size;

	i = 0;
	if (size && count > SIZE_MAX / size)
		return (NULL);
	if (size == 0 || count == 0)
	{
		count = 1;
		size = 1;
	}
	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	temp_ptr = ptr;
	while (i < (total_size))
	{
		temp_ptr[i] = 0;
		i++;
	}
	return (temp_ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	ptr = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		ptr[i] = s1[i];
	while (s2[j] != '\0')
	{
		ptr[i + j] = s2[j];
		j++;
	}
	return (ptr);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	target;

	i = 0;
	target = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == target)
		{
			return ((char *)&s[i + 1]);
		}
		i++;
	}
	if (target == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

char	*split_next_line(char	*str)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	ptr = ft_calloc(i + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (i > j)
	{
		ptr[j] = str[j];
		j++;
	}
	return (ptr);
}

int main(void)
{
	char *str1 = "b ahoj";
	char *str2 = " svete";
	char *ptr;

	ptr = ft_strchr(str1, 'h');

	printf("%s", ptr);
}
