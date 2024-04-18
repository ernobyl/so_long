/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_information.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:18:10 by emichels          #+#    #+#             */
/*   Updated: 2024/04/17 13:43:34 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	collectible_amount(char *map_str)
{
	int	i;
	int	collectibles;

	i = 0;
	collectibles = 0;
	while (map_str[i])
	{
		if (map_str[i] == 'C')
			collectibles++;
		i++;
	}
	return (collectibles);
}

void	set_map_limits(t_map *map)
{
	int		x;
	int		y;

	x = 0;
	while (map->str[x + 1] != '\n')
		x++;
	map->max_x = x;
	y = 0;
	x = 0;
	while (map->str[x + 1] != '\0')
	{
		if (map->str[x] == '\n')
		{
			if (map->str[x + 1] == '\n')
				struct_error("Error\nmap has empty line\n", map);
			y++;
		}
		x++;
	}
	map->max_y = y;
	if (map->max_x < 2 || map->max_y < 2)
		struct_error("Error\nempty line or invalid map dimensions\n", map);
	map->collect_n = collectible_amount(map->str);
}

void	is_valid_character(t_map *map)
{
	int	i;
	int	duplicate;

	i = 0;
	duplicate = 0;
	while (map->str[i])
	{
		if (map->str[i] != '\n' && map->str[i] != '1' && map->str[i] != '0'
			&& map->str[i] != 'C' && map->str[i] != 'E' && map->str[i] != 'P')
			struct_error("Error\nmap contains invalid character\n", map);
		if (map->str[i] == 'P' || map->str[i] == 'E')
			duplicate++;
		if (duplicate > 2)
			struct_error("Error\nduplicate player/exit\n", map);
		i++;
	}
	if (!ft_strchr(map->str, '1') || !ft_strchr(map->str, 'C')
		|| !ft_strchr(map->str, 'E') || !ft_strchr(map->str, 'P'))
		struct_error("Error\nmap elements missing\n", map);
}
