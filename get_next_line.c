/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:09:46 by j                 #+#    #+#             */
/*   Updated: 2025/01/07 18:33:53 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_add_to_stash(char *stash, const char *readed)
{
	char	*new_stash;

	if (!readed)
		return (stash);
	if (!stash)
		return (ft_strdup(readed));
	if (readed[0] == '\0')
		return (stash);
	new_stash = ft_strjoin(stash, readed);
	if (!new_stash)
		return (NULL);
	free(stash);
	return (new_stash);
}

int	ft_line_finded(char *stash)
{
	int	i;

	if (!stash)
		return (-1);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_extract_line(char **stash)
{
	int		newline_pos;
	char	*line;
	char	*temp;

	if (!*stash || !**stash)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	newline_pos = ft_line_finded(*stash);
	if (newline_pos >= 0)
	{
		line = ft_substr(*stash, 0, newline_pos + 1);
		temp = ft_strdup(*stash + newline_pos + 1);
	}
	else
	{
		line = ft_strdup(*stash);
		temp = NULL;
	}
	free(*stash);
	*stash = temp;
	return (line);
}

char	*ft_read_file(int fd, char *save)
{
	char	*buf;
	int		bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!save || !ft_strchr(save, '\n')))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			free(save);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		save = ft_add_to_stash(save, buf);
		if (!save)
			return (free(buf), NULL);
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read_file(fd, save);
	if (!save)
		return (NULL);
	if (!*save)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	line = ft_extract_line(&save);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur d'ouverture du fichier");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Ligne lue : %s", line);
		free(line);
	}
	close(fd);
	return (0);
}