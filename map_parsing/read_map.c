/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:31:16 by emichels          #+#    #+#             */
/*   Updated: 2024/04/15 15:55:57 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	valid_extension(char *str)
{
	int		i;
	int		k;
	char	*ext;
	
	i = 0;
	ext = ".ber";
	while (str[i] && str[i] != '.')
		i++;
	k = 0;
	while (str[i])
	{
		if (str[i] != ext[k] || k == i)
			struct_error("Error\ninvalid map format/name\n", NULL);
		i++;
		k++;
	}
}

char	*read_map(int fd)
{
	char	*map_str;
	char	*buf;
	int		len;
	char	*tmp;

	len = 1;
	map_str = ft_calloc(1, 1);
	if (!map_str)
		struct_error("Error\nmalloc failed\n", NULL);
	buf = malloc(BUFFERSIZE + 1);
	if (!buf)
	{
		free(map_str);
		struct_error("Error\nmalloc failed\n", NULL);
	}
	while (len > 0)
	{
		len = read(fd, buf, BUFFERSIZE);
		if (len <= 0)
			free (buf);
		if (len == 0)
			return (map_str);
		if (len < 0)
		{
			free (buf);
			return (NULL);
		}
		buf[len] = '\0';
		tmp = map_str;
		map_str = ft_strjoin(map_str, buf);
		free(tmp);
	}
	free(buf);
	close(fd);
	return (map_str);
}
