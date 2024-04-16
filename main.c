/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:40:26 by emichels          #+#    #+#             */
/*   Updated: 2024/04/16 13:28:30 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_map_struct(t_map *map)
{
	map->fd = 0;
	map->mlx = NULL;
	map->y = 0;
	map->x = 0;
	map->max_y = 0;
	map->max_x = 0;
	map->collect_n = 0;
	map->steps = 0;
	map->plr_y = 0;
	map->plr_x = 0;
	map->str = NULL;
	map->arr = NULL;
	map->images = NULL;
}

static void	inspect_map(t_map *map)
{
	set_map_limits(map);
	is_valid_character(map);
	is_rectangle(map);
}

static void	free_map_struct(t_map map)
{
	mlx_terminate(map.mlx);
	free(map.str);
	ft_free(map.arr);
	free_images(&map);
}

int32_t	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 2)
	{
		init_map_struct(&map);
		valid_extension(argv[1]);
		map.fd = open(argv[1], O_RDONLY);
		if (map.fd == -1)
			struct_error("Error\nfile open error\n", &map);
		read_map(&map);
		inspect_map(&map);
		map.arr = ft_split(map.str, '\n');
		if (!map.arr)
			struct_error("Error\nstring split failed\n", &map);
		mlx_set_setting(MLX_STRETCH_IMAGE, true);
		map.mlx = mlx_init((map.max_x + 1) * WIDTH, (map.max_y + 1) * HEIGHT,
				"so long", true);
		if (!map.mlx)
			struct_error((char *)mlx_strerror(mlx_errno), &map);
		display_map(&map);
		mlx_key_hook(map.mlx, &wasd_keyhook, &map);
		mlx_loop(map.mlx);
		free_map_struct(map);
	}
	return (0);
}
