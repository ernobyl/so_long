/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:51:12 by emichels          #+#    #+#             */
/*   Updated: 2024/03/20 16:33:02 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	error_msg(char *msg, int code)
{
	ft_putstr_fd(msg, 2);
	exit(code);
}

t_map	set_map_limits(char *map_str)
{
	t_map	map_limits;
	int		x;
	int		y;
	
	x = 0;
	while (map_str[x + 1] != '\n')
		x++;
	if (x < 2)
		error_msg("Error\ninvalid map width\n", EXIT_FAILURE);
	map_limits.max_x = x;
	y = 0;
	x = 0;
	while (map_str[x + 1] != '\0')
	{
		if (map_str[x] == '\n')
			y++;
		x++;
	}
	if (y < 2)
		error_msg("Error\ninvalid map height\n", EXIT_FAILURE);
	map_limits.max_y = y;
	return (map_limits);
}

void	is_rectangle(t_map map, char *map_str)
{
	char	**map_arr;
	
	map_arr = ft_split(map_str, '\n');
	map.y = 0;
	while (map_arr[map.y])
	{
		if ((int)ft_strlen(map_arr[map.y]) - 1 != map.max_x)
			error_msg("Error\nmap not rectangular\n", EXIT_FAILURE);
		map.y++;
	}	
}