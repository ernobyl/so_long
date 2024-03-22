/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:51:12 by emichels          #+#    #+#             */
/*   Updated: 2024/03/22 16:20:59 by emichels         ###   ########.fr       */
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
	ft_free(map_arr);
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
