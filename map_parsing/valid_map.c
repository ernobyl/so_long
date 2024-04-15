/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:51:12 by emichels          #+#    #+#             */
/*   Updated: 2024/04/15 15:23:15 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	is_walled(t_map *map)
{
	map->y = 0;

	while (map->y <= map->max_y)
	{
		map->x = 0;
		while (map->x <= map->max_x)
		{
			if (map->y == 0 && map->arr[map->y][map->x] != '1')
				struct_error("Error\nmap not walled\n", map);
			if (map->y == map->max_y && map->arr[map->y][map->x] != '1')
				struct_error("Error\nmap not walled\n", map);
			if (map->y != 0 && (map->arr[map->y][0] != '1' 
						|| map->arr[map->y][map->max_x] != '1'))
				struct_error("Error\nmap not walled\n", map);
			map->x++;
		}
		map->y++;
	}
}

static void	search_unfilled(char **map_arr, t_map *cur)
{
	int	i;
	int	k;

	k = 1;
	i = 1;
	while (k < cur->max_y)
	{
		i = 1;
		while (map_arr[k][i] && i < cur->max_x)
		{
			if (map_arr[k][i] == 'x')
			{
				if (map_arr[k][i + 1] != 'x' && map_arr[k][i + 1] != '1')
					traverse_path(map_arr, cur, k, i + 1);
				else if (map_arr[k][i - 1] != 'x' && map_arr[k][i - 1] != '1')
					traverse_path(map_arr, cur, k, i - 1);
				else if (map_arr[k + 1][i] != 'x' && map_arr[k + 1][i] != '1')
					traverse_path(map_arr, cur, k + 1, i);
				else if (map_arr[k - 1][i] != 'x' && map_arr[k - 1][i] != '1')
					traverse_path(map_arr, cur, k - 1, i);
			}
			i++;
		}
		k++;
	}
}

void	traverse_path(char **arr, t_map *cur, int y, int x)
{
	static int	c = 0;
	static int	e = 0;

	if (y < 1 || x < 1 || y > cur->max_y || x > cur->max_x
		|| arr[y][x] == 'x' || arr[y][x] == '1')
		return;
	if (arr[y][x] == 'C')
		c++;
	if (arr[y][x] == 'E')
		e++;
	arr[y][x] = 'x';
	traverse_path(arr, cur, y, x - 1);
	traverse_path(arr, cur, y, x + 1);
	traverse_path(arr, cur, y - 1, x);
	traverse_path(arr, cur, y + 1, x);
	search_unfilled(arr, cur);
	if (c != cur->collect_n || e < 1)
		struct_error("Error\nno valid path\n", cur);
}

static void	valid_path(t_map *begin)
{
	int		found;

	found = 0;
	begin->y = 1;
	while (begin->y < begin->max_y)
	{
		begin->x = 1;
		while (begin->arr[begin->y][begin->x])
		{
			if (begin->arr[begin->y][begin->x] == 'P')
			{
				found = 1;
				break;
			}
			begin->x++;
		}
		if (found)
			break;
		begin->y++;
	}
	traverse_path(begin->arr, begin, begin->y, begin->x);
}

void	is_rectangle(t_map *map)
{
	if (map->str[ft_strlen(map->str) - 1] == '\n' 
		|| map->str[ft_strlen_c(map->str, '\n') + 1] == '\n'
		|| map->str[0] == '\n')
		struct_error("Error\nmap has empty line\n", map);
	map->arr = ft_split(map->str, '\n');
	if (!map->arr)
		struct_error("Error\nmap has empty line\n", map);
	map->y = 0;
	while (map->arr[map->y])
	{
		if ((int)ft_strlen(map->arr[map->y]) - 1 != map->max_x)
			struct_error("Error\nmap not rectangular\n", map);
		map->y++;
	}
	is_walled(map);
	valid_path(map);
	ft_free(map->arr);
	map->arr = NULL;
}
