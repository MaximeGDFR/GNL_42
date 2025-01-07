/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:44:04 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/01/07 18:59:02 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	{
		free(stash);
		return (NULL);
	}
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
	static char	*save[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = ft_read_file(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	if (!*save[fd])
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	line = ft_extract_line(&save[fd]);
	return (line);
}

/*int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Erreur d'ouverture du fichier");
		return (1);
	}
	printf("Fichier test1.txt:\n");
	while ((line = get_next_line(fd1)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\nFichier test2.txt:\n");
	while ((line = get_next_line(fd2)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd1);
	close(fd2);
	return (0);
}*/
