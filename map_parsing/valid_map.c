/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:51:12 by emichels          #+#    #+#             */
/*   Updated: 2024/04/15 11:49:20 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	error_msg(char *msg, char *str, char **arr)
{
	if (arr)
		ft_free(arr);
	free(str);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	free_textures(t_texture *textures)
{
	mlx_delete_texture(textures->wall);
	mlx_delete_texture(textures->floor);
	mlx_delete_texture(textures->player);
	mlx_delete_texture(textures->collect);
	mlx_delete_texture(textures->door_clo);
	mlx_delete_texture(textures->door_opn);
}

static void	free_images(t_map *map)
{
	if (map->images->w_img)
		mlx_delete_image(map->mlx, map->images->w_img);
	if (map->images->f_img)
		mlx_delete_image(map->mlx, map->images->f_img);
	if (map->images->p_img)
		mlx_delete_image(map->mlx, map->images->p_img);
	if (map->images->c_img)
		mlx_delete_image(map->mlx, map->images->c_img);
	if (map->images->dc_img)
		mlx_delete_image(map->mlx, map->images->dc_img);
	if (map->images->do_img)
		mlx_delete_image(map->mlx, map->images->do_img);
	free(map->images);
}

void	struct_error(char *msg, t_map *map)
{
	if (map->arr)
		ft_free(map->arr);
	if (map->images)
		free_images(map);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	texture_error(char *msg, t_map *map, t_texture *textures)
{
	if (map->arr)
		ft_free(map->arr);
	if (textures->wall)
		mlx_delete_texture(textures->wall);
	if (textures->floor)
		mlx_delete_texture(textures->floor);
	if (textures->player)
		mlx_delete_texture(textures->player);
	if (textures->collect)
		mlx_delete_texture(textures->collect);
	if (textures->door_clo)
		mlx_delete_texture(textures->door_clo);
	if (textures->door_opn)
		mlx_delete_texture(textures->door_opn);
	free(textures);
	if (map->images)
		free_images(map);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
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

void	set_map_limits(t_map *map, char *map_str)
{
	int		x;
	int		y;
	
	x = 0;
	while (map_str[x + 1] != '\n')
		x++;
	map->max_x = x;
	y = 0;
	x = 0;
	while (map_str[x + 1] != '\0')
	{
		if (map_str[x] == '\n')
		{
			if (map_str[x + 1] == '\n')
				error_msg("Error\nmap has empty line\n", map_str, NULL);
			y++;
		}
		x++;
	}
	map->max_y = y;
	if (map->max_x < 2 || map->max_y < 2)
		error_msg("Error\ninvalid map dimensions\n", map_str, NULL);
	map->collect_n = collectible_amount(map_str);
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
				error_msg("Error\nmap not walled\n", NULL, map_arr);
			if (map.y == map.max_y && map_arr[map.y][map.x] != '1')
				error_msg("Error\nmap not walled\n", NULL, map_arr);
			if (map.y != 0 && (map_arr[map.y][0] != '1' 
						|| map_arr[map.y][map.max_x] != '1'))
				error_msg("Error\nmap not walled\n", NULL, map_arr);
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
			error_msg("Error\nmap contains invalid character\n", map_str, NULL);
		if (map_str[i] == 'P' || map_str[i] == 'E')
			duplicate++;
		if (duplicate > 2)
			error_msg("Error\nduplicate exit/start characters\n", map_str, NULL);
		i++;
	}
	if (!ft_strchr(map_str, '1') || !ft_strchr(map_str, 'C')
		|| !ft_strchr(map_str, 'E') || !ft_strchr(map_str, 'P'))
		error_msg("Error\nmap elements missing\n", map_str, NULL);
}

static void	search_unfilled(char **map_arr, t_map cur)
{
	int	i;
	int	k;

	k = 1;
	i = 1;
	while (k < cur.max_y)
	{
		i = 1;
		while (map_arr[k][i] && i < cur.max_x)
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

void	traverse_path(char **map_arr, t_map cur, int y, int x)
{
	static int	c = 0;
	static int	e = 0;

	if (y < 1 || x < 1 || y > cur.max_y || x > cur.max_x
		|| map_arr[y][x] == 'x' || map_arr[y][x] == '1')
		return;
	if (map_arr[y][x] == 'C')
		c++;
	if (map_arr[y][x] == 'E')
		e++;
	map_arr[y][x] = 'x';
	traverse_path(map_arr, cur, y, x - 1);
	traverse_path(map_arr, cur, y, x + 1);
	traverse_path(map_arr, cur, y - 1, x);
	traverse_path(map_arr, cur, y + 1, x);
	search_unfilled(map_arr, cur);
	if (c != cur.collect_n || e < 1)
		error_msg("Error\nno valid path\n", NULL, map_arr);
}

static void	valid_path(char **map_arr, t_map begin)
{
	int		found;

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
	traverse_path(map_arr, begin, begin.y, begin.x);
}

void	is_rectangle(t_map map, char *map_str)
{
	char	**map_arr;
	
	if (map_str[ft_strlen(map_str) - 1] == '\n' 
		|| map_str[ft_strlen_c(map_str, '\n') + 1] == '\n'
		|| map_str[0] == '\n')
		error_msg("Error\nmap has empty line\n", map_str, NULL);
	map_arr = ft_split(map_str, '\n');
	if (!map_arr)
		error_msg("Error\nmap has empty line\n", map_str, map_arr);
	map.y = 0;
	while (map_arr[map.y])
	{
		if ((int)ft_strlen(map_arr[map.y]) - 1 != map.max_x)
			error_msg("Error\nmap not rectangular\n", map_str, map_arr);
		map.y++;
	}
	is_walled(map_arr, map);
	valid_path(map_arr, map);
	ft_free(map_arr);
}
