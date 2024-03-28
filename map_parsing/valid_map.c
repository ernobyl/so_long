/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:51:12 by emichels          #+#    #+#             */
/*   Updated: 2024/03/28 15:27:37 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	error_msg(char *msg, int code, char *str, char **arr)
{
	if (arr)
		ft_free(arr);
	free(str);
	ft_putstr_fd(msg, 2);
	exit(code);
}

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

t_map	set_map_limits(char *map_str)
{
	t_map	map_limits;
	int		x;
	int		y;
	
	x = 0;
	while (map_str[x + 1] != '\n')
		x++;
	map_limits.max_x = x;
	y = 0;
	x = 0;
	while (map_str[x + 1] != '\0')
	{
		if (map_str[x] == '\n')
		{
			if (map_str[x + 1] == '\n')
				error_msg("Error\nmap has empty line\n", EXIT_FAILURE, map_str, NULL);
			y++;
		}
		x++;
	}
	map_limits.max_y = y;
	if (map_limits.max_x < 2 || map_limits.max_y < 2)
		error_msg("Error\ninvalid map dimensions\n", EXIT_FAILURE, map_str, NULL);
	map_limits.collect_n = collectible_amount(map_str);
	return (map_limits);
}

static void	is_walled(char **map_arr, t_map map)
{
	map.y = 0;

	while (map.y <= map.max_y)
	{
		map.x = 0;
		while (map.x <= map.max_x)
		{
			if (map.y == 0 && map_arr[map.y][map.x] != '1')
				error_msg("Error\nmap not walled\n", EXIT_FAILURE, NULL, map_arr);
			if (map.y == map.max_y && map_arr[map.y][map.x] != '1')
				error_msg("Error\nmap not walled\n", EXIT_FAILURE, NULL, map_arr);
			if (map.y != 0 && (map_arr[map.y][0] != '1' 
						|| map_arr[map.y][map.max_x] != '1'))
				error_msg("Error\nmap not walled\n", EXIT_FAILURE, NULL, map_arr);
			map.x++;
		}
		map.y++;
	}
}

void	is_valid_character(char *map_str)
{
	int	i;
	int	duplicate;

	i = 0;
	duplicate = 0;
	while (map_str[i])
	{
		if (map_str[i] != '\n' && map_str[i] != '1' && map_str[i] != '0'
			&& map_str[i] != 'C' && map_str[i] != 'E' && map_str[i] != 'P')
			error_msg("Error\nmap contains invalid character\n", EXIT_FAILURE, map_str, NULL);
		if (map_str[i] == 'P' || map_str[i] == 'E')
			duplicate++;
		if (duplicate > 2)
			error_msg("Error\nduplicate exit/start characters\n", EXIT_FAILURE, map_str, NULL);
		i++;
	}
	if (!ft_strchr(map_str, '1') || !ft_strchr(map_str, 'C')
		|| !ft_strchr(map_str, 'E') || !ft_strchr(map_str, 'P'))
		error_msg("Error\nmap elements missing\n", EXIT_FAILURE, map_str, NULL);
}

// static int	search_unfilled(char **map_arr, t_map cur)
// {
// 	int	i;
// 	int	k;

// 	k = 1;
// 	while (k < cur.max_y)
// 	{
// 		i = 1;
// 		while (map_arr[k][i])
// 		{
// 			if (map_arr[k][i] == 'x')
// 			{
// 				if ((map_arr[k][i + 1] != 'x' && map_arr[k][i + 1] != '1')
// 					|| (map_arr[k][i - 1] != 'x' && map_arr[k][i - 1] != '1'))
// 					return (i);
// 				if ((map_arr[k + 1][i] != 'x' && map_arr[k + 1][i] != '1')
// 					|| (map_arr[k - 1][i] != 'x' && map_arr[k - 1][i] != '1'))
// 					return (k);
// 			}
// 			i++;
// 		}
// 		k++;
// 	}
// 	return (0);
// }

static void	traverse_path(char **map_arr, t_map cur, int y, int x)
{
	static int	c = 0;
	static int	e = 0;

	//printf("max y: %i, max x: %i\n", cur.max_y, cur.max_x);
	printf("current char %c\n", map_arr[y][x]);
	if (map_arr[y][x] == 'x' || map_arr[y][x] == '1')
		return;
	if (map_arr[y][x] == 'C')
		c++;
	if (map_arr[y][x] == 'E')
		e++;
	map_arr[y][x] = 'x';
	printf("y: %i, x: %i\n", y, x);
	int k = 0;
	while (map_arr[k])
	{
		printf("%s\n", map_arr[k]);
		k++;
	}
	printf("c: %i, e: %i\n", c, e);
	// if (map_arr[y][x] == 'x' && ((map_arr[y][x - 1] == 'x' || map_arr[y][x - 1] == '1')
	// 	|| (map_arr[y][x + 1] == 'x' || map_arr[y][x + 1] == '1')))
	// 	x = search_unfilled(map_arr, cur);
	// else if (map_arr[y][x] == 'x' && ((map_arr[y - 1][x] == 'x' || map_arr[y - 1][x] == '1')
	// 	|| (map_arr[y + 1][x] == 'x' || map_arr[y + 1][x] == '1')))
	// 	y = search_unfilled(map_arr, cur);
	traverse_path(map_arr, cur, y, x - 1);
	traverse_path(map_arr, cur, y, x + 1);
	traverse_path(map_arr, cur, y - 1, x);
	traverse_path(map_arr, cur, y + 1, x);
	if (c != cur.collect_n || e < 1)
		error_msg("Error\nno valid path to exit\n", EXIT_FAILURE, NULL, map_arr);
}

static void	valid_path(char **map_arr, t_map begin)
{
	int		found;
	char	**map_tmp;

	found = 0;
	begin.y = 1;
	while (begin.y < begin.max_y)
	{
		begin.x = 1;
		while (map_arr[begin.y][begin.x])
		{
			if (map_arr[begin.y][begin.x] == 'P')
			{
				found = 1;
				break;
			}
			begin.x++;
		}
		if (found)
			break;
		begin.y++;
	}
	map_tmp = map_arr;
	traverse_path(map_tmp, begin, begin.y, begin.x);
	ft_free(map_tmp);
}

void	is_rectangle(t_map map, char *map_str)
{
	char	**map_arr;
	
	if (map_str[ft_strlen(map_str) - 1] == '\n' 
		|| map_str[ft_strlen_c(map_str, '\n') + 1] == '\n'
		|| map_str[0] == '\n')
		error_msg("Error\nmap has empty line\n", EXIT_FAILURE, map_str, NULL);
	map_arr = ft_split(map_str, '\n');
	if (!map_arr)
		error_msg("Error\nmap has empty line\n", EXIT_FAILURE, map_str, map_arr);
	map.y = 0;
	while (map_arr[map.y])
	{
		if ((int)ft_strlen(map_arr[map.y]) - 1 != map.max_x)
			error_msg("Error\nmap not rectangular\n", EXIT_FAILURE, map_str, map_arr);
		map.y++;
	}
	is_walled(map_arr, map);
	valid_path(map_arr, map);
	ft_free(map_arr);
}
