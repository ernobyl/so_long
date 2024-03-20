/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:31:16 by emichels          #+#    #+#             */
/*   Updated: 2024/03/20 14:11:03 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*read_map(int fd)
{
	char	*map_str;
	char	*buf;
	int		len;

	len = 1;
	map_str = ft_calloc(1, 1);
	buf = malloc(BUFFERSIZE + 1);
	while (len > 0)
	{
		len = read(fd, buf, BUFFERSIZE);
		if (len <= 0)
			free (buf);
		if (len == 0)
			return (map_str);
		if (len < 0)
			return (NULL);
		buf[len] = '\0';
		map_str = ft_strjoin(map_str, buf);
	}
	close(fd);
	return (map_str);
}
